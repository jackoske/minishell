# HOW WE KEEP IN SYNC
When you rebase in Git, it follows a strategy similar to a "forward strategy." Rebasing involves taking a series of commits from one branch and reapplying them on top of another branch. This moves the base of your branch forward to a new point in history.

### Steps of Rebase

1. **Identify Common Ancestor**: Git finds the common ancestor between the branch you are rebasing (e.g., `feature`) and the branch you are rebasing onto (e.g., `main` or `master`).
2. **Reapply Commits**: Git replays each commit from your `feature` branch that isn't in `main` on top of the latest commit in `main`. This effectively moves the base of `feature` forward to the head of `main`.

This results in a linear commit history, making it appear as if all changes were made in a straightforward, sequential manner.

### Example

Assume the following commit history:

```
A---B---C main
     \
      D---E---F feature
```

If you perform a rebase of `feature` onto `main`:

```sh
git checkout feature
git rebase main
```

The history will be rewritten to:

```
A---B---C---D'---E'---F' feature
```

Here, `D'`, `E'`, and `F'` are the new commits created by reapplying `D`, `E`, and `F` on top of `C`.

### Benefits

- **Linear History**: It makes the history of the project cleaner and easier to read.
- **Conflict Resolution**: Any conflicts that arise during the rebase are resolved immediately, reducing the likelihood of future conflicts when merging the `feature` branch back into `main`.

