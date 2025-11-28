# Contributing to BestiolesEcosystem

## Workflow

1.  **Create a new branch**
    Create a new branch from the default one (`production`).
    ```bash
    git checkout production
    git checkout -b fix-for-10 # or feature/new-awesome-feature
    ```

2.  **Develop**
    Develop locally on your branch, commit and push your changes as you're making progress.

3.  **Verify**
    When you're done, verify everything works by running:
    ```bash
    make actions
    ```
    - The first action (compilation) is **necessary** to be merged with the default branch.
    - The second action (linting) is not required to merge but it is still worth trying to get it to pass to maintain a cohesive codebase.

4.  **Push and Pull Request**
    If the code compiles successfully and your new code seems to be doing what it's supposed to do, you can then do a pull request.

    **Push your changes**:
    ```bash
    git push -u origin <your-branch-name>
    ```

    **Create Pull Request**:
    *   **Via CLI**:
        ```bash
        gh pr create
        ```
    *   **Via GitHub Interface**:
        Go to the repository page. You should see a banner for your recently pushed branch. Click **Compare & pull request**.
