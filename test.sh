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

# 1. DEFINITION DE LA FONCTION (Doit être en haut)
test_cmd() {
    local cmd="$1"
    
    # On récupère la sortie et le code de retour de Bash
    BASH_OUT=$(echo -n "$cmd" | $BASH 2>/dev/null)
    BASH_RET=$?

    # On récupère la sortie et le code de retour de ton Minishell
    MINI_OUT=$(echo "$cmd" | $MINISHELL 2>/dev/null)
    MINI_RET=$?

    # Comparaison
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

# 2. EXECUTION DES TESTS DEPUIS COMMANDS.TXT
if [ -f "commands.txt" ]; then
    echo -e "${Y}### TESTS DEPUIS COMMANDS.TXT ###${NC}"
    while IFS= read -r line; do
        # Ignore les lignes vides et les commentaires
        [[ -z "$line" || "$line" == "#"* ]] && continue
        test_cmd "$line"
    done < commands.txt
fi

# 3. TESTS MANUELS (Optionnels si déjà dans commands.txt)
echo -e "\n${Y}### TESTS MANUELS ###${NC}"
test_cmd "ls"
test_cmd "echo hello"

echo -e "\n${Y}Vérifie le fichier ${R}errors.log${NC} pour les détails des échecs."