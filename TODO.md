# Minishell - TODO List

## Fonctionnalités Essentielles
- [x] Afficher un prompt en attente de nouvelles commandes
- [x] Implémenter l'historique des commandes
- [x] Gérer le PATH et les commandes avec leurs paramètres
- [x] Gérer les quotes (simples et doubles)
- [x] Implémenter les redirections:
  - [x] `<` (entrée)
  - [x] `>` (sortie)
  - [x] `>>` (sortie en mode append)
  - [ ] `<<` (heredoc)
- [x] Implémenter les pipes `|`
- [x] Gérer les variables d'environnement (`$VAR`)
- [ ] Gérer `$?` (code de retour)
- [x] Implémenter les signaux:
  - [x] Ctrl-C (afficher nouveau prompt)
  - [x] Ctrl-D (quitter)
  - [x] Ctrl-\ (ne rien faire)

## Builtins à Implémenter
- [x] `echo` avec option `-n`
- [x] `cd` avec chemin relatif ou absolu
- [x] `pwd` sans options
- [x] `export` sans options
- [x] `unset` sans options
- [x] `env` sans options ni arguments
- [x] `exit` sans options

## Tests et Gestion d'Erreurs
- [x] Tester les cas d'erreurs de syntaxe
- [ ] Vérifier les fuites mémoire
- [ ] Tester les cas limites:
  - [ ] Commandes très longues
  - [x] Multiples pipes
  - [x] Quotes non fermées
  - [ ] Caractères spéciaux

## Optimisations et Améliorations
- [ ] Nettoyer le code et la gestion mémoire
- [x] Améliorer la gestion des erreurs
- [x] Optimiser le parsing des commandes
- [ ] Documenter le code
- [ ] Vérifier la norme 42

## Tests Spécifiques à Faire
- [ ] Tester avec `valgrind`
- [ ] Comparer le comportement avec bash
- [ ] Tester les cas suivants:
  - [ ] `echo $PATH`
  - [ ] `echo "$PATH"`
  - [ ] `echo '$PATH'`
  - [ ] `cat << EOF`
  - [x] `ls | grep a | wc -l`

## Points à Améliorer
1. Implémenter le heredoc (`<<`)
2. Gérer la variable `$?` pour les codes de retour
3. Vérifier et corriger les fuites mémoire
4. Tester les cas limites manquants
5. Documenter le code
6. Vérifier la conformité avec la norme 42
7. Effectuer des tests approfondis avec valgrind
8. Comparer systématiquement le comportement avec bash

## Notes
- Votre implémentation des builtins est complète
- La gestion des pipes et des redirections de base est bien implémentée
- La gestion des signaux est en place
- Le parsing des commandes et des quotes fonctionne correctement 