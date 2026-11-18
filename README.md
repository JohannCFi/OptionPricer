# Option Pricer — C++ for Finance (ESILV A4, 2026)

Bibliothèque C++ de pricing d'options : formules fermées de Black-Scholes, arbre binomial Cox-Ross-Rubinstein (CRR), Monte Carlo pour les options path-dependent, et options américaines.

**Équipe :** Charles · Clement · Johann · Paul
**Deadline :** 22 décembre 2026, 11h00

---

## Contenu du projet

### Partie I — Modèle de Black-Scholes
| Classe | Rôle |
|---|---|
| `Option` | Classe abstraite : `_expiry`, `getExpiry()`, `payoff(double)` virtuelle pure |
| `EuropeanVanillaOption` | Abstraite, dérive d'`Option` : `_strike`, `enum class optionType { call, put }`, `GetOptionType()` |
| `CallOption` / `PutOption` | Payoffs `(z − K)⁺` et `(K − z)⁺` |
| `BlackScholesPricer` | `operator()` → prix, `delta()` → delta (via `std::erfc`) ; classe amie d'`EuropeanVanillaOption` |

### Partie II — Modèle Cox-Ross-Rubinstein
| Classe | Rôle |
|---|---|
| `BinaryTree<T>` | Template : `_depth`, `_tree` (vector de vectors), `setDepth`, `setNode`, `getNode`, `display` |
| `CRRPricer` | `compute()` (induction backward), `get(n, i)`, `operator()(bool closed_form = false)`, vérification d'arbitrage `D < R < U` |
| `EuropeanDigitalOption` + `EuropeanDigitalCallOption` / `EuropeanDigitalPutOption` | Payoffs `1{z ≥ K}` et `1{z ≤ K}`, aussi pricés par `BlackScholesPricer` |

### Partie III — Options path-dependent et Monte Carlo
| Classe | Rôle |
|---|---|
| `Option::payoffPath(std::vector<double>)` | Payoff sur une trajectoire (par défaut `h(S_tm)`) |
| `AsianOption` + `AsianCallOption` / `AsianPutOption` | Payoff sur la moyenne arithmétique des `S_tk` |
| `MT` | Singleton encapsulant `std::mt19937` : `rand_unif()`, `rand_norm()` |
| `BlackScholesMCPricer` | `generate(nb_paths)`, `operator()`, `confidenceInterval()` (IC 95 %), `getNbPaths()` |

### Partie IV — Retour sur CRR : options américaines
| Classe | Rôle |
|---|---|
| `AmericanOption` + `AmericanCallOption` / `AmericanPutOption` | `isAmericanOption()` surchargée |
| `CRRPricer` (étendu) | Politique d'exercice anticipé dans un `BinaryTree<bool>` (`getExercise(n, i)`), constructeur `(option, depth, S0, r, σ)` avec approximation de Black-Scholes |

---

## Structure du dépôt

```
Projet_Pricer_Cpp/
├── Projet_Pricer_Cpp.sln          # Solution Visual Studio
├── Projet_Pricer_Cpp/             # Sources (.h / .cpp)
├── .gitignore
└── README.md
```

## Compilation

Ouvrir `Projet_Pricer_Cpp.sln` dans Visual Studio 2022 et compiler (C++17 ou plus).
Les fichiers de test avec les `main()` de notation sont disponibles sur DVL.

---

## Workflow Git

```
Charles ─┐
Clement ─┤
Johann  ─┼──► pre-main ──► main
Paul    ─┘
```

- Chacun développe sur **sa branche perso**.
- Intégration via Pull Request **branche perso → `pre-main`**.
- Quand `pre-main` est stable et testée : PR **`pre-main` → `main`**.
- Avant de commencer à travailler, récupérer les dernières intégrations :
  ```bash
  git checkout <ma-branche>
  git pull origin pre-main
  ```

---

## Consignes de rendu

- Archive `.zip` envoyée par e-mail au chargé de TD, **toute l'équipe en CC**.
- Objet de l'e-mail : **`C++ for Finance project 2026`**.
- Le zip ne contient **que des fichiers `.cpp` et `.h`**, taille **≤ 1 Mo**, en pièce jointe (pas de lien).
- Nom du fichier : nom de famille du représentant (premier nom dans l'ordre alphabétique, hors MA).
- **Aucune fonction `main()`** dans le rendu.
- **Aucun membre public supplémentaire** par rapport à l'énoncé.
