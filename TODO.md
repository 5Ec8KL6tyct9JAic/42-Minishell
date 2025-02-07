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
  - [x] `<<` (heredoc)
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

## Nouvelles Tâches
- [ ] Refactoring et Organisation du Code
  - [ ] Réorganiser les fichiers dans des dossiers thématiques
  - [ ] Séparer les fonctions en modules plus petits
  - [ ] Uniformiser les noms de fonctions et variables
  - [ ] Ajouter des commentaires descriptifs

- [ ] Gestion des Erreurs
  - [ ] Implémenter un système unifié de gestion d'erreurs
  - [ ] Ajouter des messages d'erreur plus descriptifs
  - [ ] Gérer les cas d'erreur manquants

- [ ] Améliorations de Performance
  - [ ] Optimiser la gestion de la mémoire
  - [ ] Réduire les allocations/libérations inutiles
  - [ ] Améliorer la vitesse de parsing

- [ ] Tests et Validation
  - [ ] Créer une suite de tests unitaires
  - [ ] Tester les cas limites
  - [ ] Vérifier la conformité avec bash

## Tests Spécifiques à Faire
- [ ] Tests de Mémoire
  - [ ] Valgrind sur toutes les commandes
  - [ ] Vérifier les fuites dans les pipes
  - [ ] Tester les cas d'allocation échouée

- [ ] Tests Fonctionnels
  - [ ] Tester les combinaisons de redirections
  - [ ] Vérifier le comportement avec de longues commandes
  - [ ] Tester les cas d'erreur de syntaxe

- [ ] Tests de Robustesse
  - [ ] Tester avec des entrées malformées
  - [ ] Vérifier la gestion des signaux pendant l'exécution
  - [ ] Tester les limites de mémoire

## Documentation
- [ ] Ajouter des commentaires de fonction complets
- [ ] Créer un guide d'utilisation
- [ ] Documenter les choix d'implémentation
- [ ] Ajouter des exemples d'utilisation

## Optimisations Futures
- [ ] Améliorer la gestion des variables d'environnement
- [ ] Optimiser le parsing des commandes complexes
- [ ] Ajouter la complétion de commandes
- [ ] Implémenter l'historique persistant

## Notes
- La structure de base est solide
- Les builtins sont tous implémentés
- La gestion des signaux fonctionne bien
- Le parsing est fonctionnel mais peut être optimisé
- La gestion de la mémoire nécessite une attention particulière 