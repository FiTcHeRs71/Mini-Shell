#!/bin/bash

# --- CONFIGURATION ---
MINISHELL="./minishell"
BASH="bash"
LOG="errors.log"
> $LOG

# Couleurs
G='\033[0;32m'
R='\033[0;31m'
Y='\033[0;33m'
NC='\033[0m'

test_cmd() {
    local cmd="$1"
    
    # 1. On récupère la sortie et le code de retour de Bash
    BASH_OUT=$(echo -n "$cmd" | $BASH 2>/dev/null)
    BASH_RET=$?

    # 2. On récupère la sortie et le code de retour de ton Minishell
    MINI_OUT=$(echo -n "$cmd" | $MINISHELL 2>/dev/null)
    MINI_RET=$?

    # 3. Comparaison
    if [ "$BASH_OUT" == "$MINI_OUT" ] && [ "$BASH_RET" == "$MINI_RET" ]; then
        printf "${G}[OK]${NC} %s\n" "$cmd"
    else
        printf "${R}[KO]${NC} %s\n" "$cmd"
        {
            echo "COMMAND: $cmd"
            echo "EXPECTED (BASH): '$BASH_OUT' | RET: $BASH_RET"
            echo "ACTUAL (MINI)  : '$MINI_OUT' | RET: $MINI_RET"
            echo "------------------------------------"
        } >> $LOG
    fi
}
while IFS= read -r line; do
    test_cmd "$line"
done < commands.txt
# --- SÉLECTION DES TESTS DU SHEET (EXEMPLE DES BLOCS MAJEURS) ---

echo -e "${Y}### TESTS : COMMANDES SIMPLES & PATH ###${NC}"
test_cmd "ls"
test_cmd "ls -la"
test_cmd "/bin/ls"
test_cmd "   ls   -la    "
test_cmd "empty_command" # Doit retourner 127

echo -e "\n${Y}### TESTS : ECHO & QUOTES ###${NC}"
test_cmd "echo hello"
test_cmd "echo -n hello"
test_cmd "echo 'single quotes'"
test_cmd "echo \"double quotes\""
test_cmd "echo '\"double inside single\"'"
test_cmd "echo \"'single inside double'\""

echo -e "\n${Y}### TESTS : REDIRECTIONS ###${NC}"
test_cmd "echo test > f1 ; cat f1 ; rm f1"
test_cmd "echo hello >> f2 ; echo world >> f2 ; cat f2 ; rm f2"
test_cmd "cat < Makefile"

echo -e "\n${Y}### TESTS : PIPES ###${NC}"
test_cmd "ls | grep m | wc -l"
test_cmd "cat Makefile | grep CC | head -n 1"
test_cmd "ls | ls | ls | ls"

echo -e "\n${Y}### TESTS : VARIABLES D'ENV ###${NC}"
test_cmd "echo \$USER"
test_cmd "export VAR=test ; echo \$VAR"
test_cmd "export VAR=test ; unset VAR ; echo \$VAR"

echo -e "\n${Y}### TESTS : CODES DE RETOUR ###${NC}"
test_cmd "false"
test_cmd "echo \$?"
test_cmd "ls /filename_zero_exist"
test_cmd "echo \$?"

echo -e "\n${Y}Vérifie le fichier ${R}errors.log${NC} pour les détails des échecs."