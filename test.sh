#!/bin/bash

# ==============================================================================
#  TESTER MINISHELL - Basé sur la Checklist fil_rouge.txt
# ==============================================================================

MINISHELL_PATH="./minishell"
BASH_PATH="bash"
VALGRIND_LOG="valgrind_test.log"

# Couleurs
RESET="\033[0m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
CYAN="\033[36m"
BOLD="\033[1m"

# Compteurs
TOTAL=0
PASSED=0
FAILED=0

# Nettoyage pré-test
rm -f outfile output.txt append.txt result.txt file1 file2 input.txt
echo "Ceci est un fichier test" > input.txt
touch file_vide

function print_banner() {
    echo -e "${CYAN}======================================================${RESET}"
    echo -e "${CYAN}       LANCEMENT DES TESTS MINISHELL v1.0             ${RESET}"
    echo -e "${CYAN}======================================================${RESET}"
}

function exec_test() {
    local TEST_NAME="$1"
    local CMD="$2"
    
    ((TOTAL++))
    
    # Exécution Bash (Référence)
    echo "$CMD" | $BASH_PATH > bash_out 2> bash_err
    RET_BASH=$?
    
    # Exécution Minishell
    # On filtre "Minishell > " car readline l'affiche parfois même en pipe
    echo "$CMD" | $MINISHELL_PATH > mini_out 2> mini_err
    RET_MINI=$?
    
    # Nettoyage des sorties pour comparaison (suppression du prompt si présent)
    # Note: On ignore souvent stderr dans les tests simples car les messages d'erreur varient,
    # mais on peut vérifier si les deux ont produit une erreur ou non.
    
    # Comparaison Stdout
    DIFF_OUT=$(diff -u bash_out mini_out)
    
    # Comparaison Return Code (Uniquement pour exit ou si demandé explicitement)
    # Bash retourne le status du dernier pipe, minishell aussi normalement.
    
    if [ "$DIFF_OUT" == "" ]; then
        # Check Return Code
        if [ $RET_BASH -eq $RET_MINI ]; then
            echo -e "${GREEN}[OK]${RESET} ${BOLD}$TEST_NAME${RESET}"
            ((PASSED++))
        else
            # Tolérance sur le code d'erreur (ex: 1 vs 2) pour les erreurs customs
            if [ $RET_BASH -ne 0 ] && [ $RET_MINI -ne 0 ]; then
                 echo -e "${GREEN}[OK]${RESET} ${BOLD}$TEST_NAME${RESET} (Diff Exit: B=$RET_BASH M=$RET_MINI - Acceptable)"
                 ((PASSED++))
            else
                echo -e "${RED}[KO]${RESET} ${BOLD}$TEST_NAME${RESET} -> Mauvais Exit Code"
                echo -e "   CMD: $CMD"
                echo -e "   Bash: $RET_BASH | Minishell: $RET_MINI"
                ((FAILED++))
            fi
        fi
    else
        echo -e "${RED}[KO]${RESET} ${BOLD}$TEST_NAME${RESET} -> Stdout Différent"
        echo -e "   CMD: $CMD"
        echo -e "${YELLOW}--- Bash Output ---${RESET}"
        cat bash_out
        echo -e "${YELLOW}--- Mini Output ---${RESET}"
        cat mini_out
        echo -e "${YELLOW}--- Diff ---${RESET}"
        echo "$DIFF_OUT"
        ((FAILED++))
    fi
}

print_banner

# ==============================================================================
# 1. COMMANDES BASIQUES
# ==============================================================================
echo -e "\n${CYAN}--- Commandes Basiques ---${RESET}"
exec_test "Empty command" ""
exec_test "Spaces" "   "
exec_test "Simple ls" "ls"
exec_test "ls avec args" "ls -la"
exec_test "pwd" "pwd"
exec_test "echo simple" "echo hello world"
exec_test "echo -n" "echo -n no newline"
exec_test "echo multiple args" "echo one two three"

# ==============================================================================
# 2. BUILT-INS
# ==============================================================================
echo -e "\n${CYAN}--- Built-ins ---${RESET}"
# Note: Pour cd et export, on doit vérifier l'effet dans la même ligne de commande
exec_test "cd absolute" "cd /tmp && pwd"
exec_test "cd relative" "mkdir -p test_dir && cd test_dir && pwd && cd .. && rmdir test_dir"
exec_test "export & echo" "export MY_VAR=toto && echo \$MY_VAR"
exec_test "export with spaces" "export MY_VAR=\"valeur avec espaces\" && echo \$MY_VAR"
exec_test "unset" "export DEL_VAR=test && unset DEL_VAR && echo \$DEL_VAR"
exec_test "env basic" "env | grep PATH" # On grep pour éviter de diff tout l'env qui peut varier légèrement (_=...)
exec_test "Exit value" "exit 42" 

# ==============================================================================
# 3. REDIRECTIONS
# ==============================================================================
echo -e "\n${CYAN}--- Redirections ---${RESET}"
exec_test "Redir >" "echo 'test 123' > output.txt && cat output.txt"
exec_test "Redir >>" "echo 'line1' > append.txt && echo 'line2' >> append.txt && cat append.txt"
exec_test "Redir <" "cat < input.txt"
exec_test "Complex Redir" "ls -la > file1 && cat < file1 | grep Makefile > file2 && cat file2"

# ==============================================================================
# 4. PIPES
# ==============================================================================
echo -e "\n${CYAN}--- Pipes ---${RESET}"
exec_test "Simple Pipe" "ls | grep Makefile"
exec_test "Double Pipe" "ls -la | grep src | wc -l"
exec_test "Pipe & Redir" "cat input.txt | grep fichier > result.txt && cat result.txt"
exec_test "Echo Pipe Cat" "echo 'test' | cat -e"

# ==============================================================================
# 5. EXPANSION & QUOTES
# ==============================================================================
echo -e "\n${CYAN}--- Expansion & Quotes ---${RESET}"
exec_test "Single Quotes" "echo '\$USER'"     # Doit afficher $USER littéralement
exec_test "Double Quotes" "echo \"\$USER\""   # Doit afficher le nom de l'utilisateur
exec_test "Exit Status \$?" "ls /nonexistent; echo \$?"
exec_test "Mixed Quotes" "echo \"'test'\""
exec_test "Sequential Logic" "echo test; echo suite"

# ==============================================================================
# 6. EDGE CASES
# ==============================================================================
echo -e "\n${CYAN}--- Edge Cases (Peuvent échouer selon implémentation) ---${RESET}"
# Ces tests sont délicats car bash gère certaines erreurs de syntaxe différemment
exec_test "Pipe vide fin" "ls |" # Devrait faire erreur syntaxe
exec_test "Pipe vide début" "| ls"
exec_test "Triple Pipe" "|||"
exec_test "Redir invalide" "< > file"

# ==============================================================================
# RÉSULTATS
# ==============================================================================
echo -e "\n${CYAN}======================================================${RESET}"
echo -e "TESTS TERMINÉS"
echo -e "Total: $TOTAL"
echo -e "${GREEN}Passed: $PASSED${RESET}"
if [ $FAILED -gt 0 ]; then
    echo -e "${RED}Failed: $FAILED${RESET}"
else
    echo -e "${GREEN}TOUS LES TESTS SONT PASSÉS ! BRAVO !${RESET}"
fi

# Nettoyage final
rm -f bash_out bash_err mini_out mini_err output.txt append.txt result.txt file1 file2 input.txt file_vide