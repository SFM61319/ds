# Welcome to ds contributing guide <!-- omit in toc -->

Thank you for investing your time in contributing to our project! Any
contribution you make will be reflected on the next release of ds and on
[ds docs](https://sfm61319.github.io/ds/) and programs using ds :sparkles:.

Read our [Code of Conduct](./CODE_OF_CONDUCT.md) to keep our community
approachable and respectable.

In this guide you will get an overview of the contribution workflow from opening
an issue, creating a PR, reviewing, and merging the PR.

Use the table of contents icon on the top left corner of this document to get to
a specific section of this guide quickly.

## New contributor guide

To get an overview of the project, read the [README](./README.md). Here are some
resources to help you get started with open source contributions:

- [Finding ways to contribute to open source on GitHub](https://docs.github.com/en/get-started/exploring-projects-on-github/finding-ways-to-contribute-to-open-source-on-github)
- [Set up Git](https://docs.github.com/en/get-started/quickstart/set-up-git)
- [GitHub flow](https://docs.github.com/en/get-started/quickstart/github-flow)
- [Collaborating with pull requests](https://docs.github.com/en/github/collaborating-with-pull-requests)

## Getting started

### Issues

#### Create a new issue

If you spot a problem with the repository,
[search if an issue already exists](https://docs.github.com/en/github/searching-for-information-on-github/searching-on-github/searching-issues-and-pull-requests#search-by-the-title-body-or-comments).
If a related issue doesn't exist, you can open a new issue using a relevant
[issue form](https://github.com/SFM61319/ds/issues/new/choose).

#### Solve an issue

Scan through our [existing issues](https://github.com/SFM61319/ds/issues)
to find one that interests you. You can narrow down the search using `labels`
as filters. See
[Labels](https://docs.github.com/en/issues/using-labels-and-milestones-to-track-work/managing-labels)
for more information. As a general rule, we don’t assign issues to anyone. If
you find an issue to work on, you are welcome to open a PR with a fix.

### Make Changes

#### Make changes in the UI

Click **Make a contribution** at the bottom of any source page to make small
changes such as a typo, sentence fix, or a broken link. This takes you to the
`.md` file where you can make your changes and
[create a pull request](#pull-request) for a review.

#### Make changes in a codespace

For more information about using a codespace, see
[GitHub Codespaces](https://docs.github.com/en/codespaces/overview).

#### Make changes locally

1. Fork the repository.

- Using GitHub Desktop:

  - [Getting started with GitHub Desktop](https://docs.github.com/en/desktop/installing-and-configuring-github-desktop/getting-started-with-github-desktop)
    will guide you through setting up Desktop.
  - Once Desktop is set up, you can use it to
    [fork the repo](https://docs.github.com/en/desktop/contributing-and-collaborating-using-github-desktop/cloning-and-forking-repositories-from-github-desktop)!

- Using the command line:
  - [Fork the repo](https://docs.github.com/en/github/getting-started-with-github/fork-a-repo#fork-an-example-repository)
    so that you can make your changes without affecting the original project
    until you're ready to merge them.

2. Install:

- A C/C++ Compiler.
- [**CMake**](https://cmake.org/).
- And optionally:
  - [**Visual Studio Code**](https://code.visualstudio.com/).
  - [**Microsoft's C/C++ Extension Pack for Visual Studio Code**](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack)

3. Create a working branch (with a name in the form
   `<your-username>/<your-contribution>`) and start with your changes!

### Commit your update

Commit the changes once you are happy with them. Don't forget to self-review to
speed up the review process:zap:.

### Pull Request

When you're finished with the changes, create a pull request, also known as a
PR.

- Fill the "Ready for review" template so that we can review your PR. This
  template helps reviewers understand your changes as well as the purpose of
  your pull request.
- Don't forget to
  [link PR to issue](https://docs.github.com/en/issues/tracking-your-work-with-issues/linking-a-pull-request-to-an-issue)
  if you are solving one.
- Enable the checkbox to
  [allow maintainer edits](https://docs.github.com/en/github/collaborating-with-issues-and-pull-requests/allowing-changes-to-a-pull-request-branch-created-from-a-fork)
  so the branch can be updated for a merge. Once you submit your PR, a ds team
  member will review your proposal. We may ask questions or request additional
  information.
- We may ask for changes to be made before a PR can be merged, either using
  [suggested changes](https://docs.github.com/en/github/collaborating-with-issues-and-pull-requests/incorporating-feedback-in-your-pull-request)
  or pull request comments. You can apply suggested changes directly through the
  UI. You can make any other changes in your fork, then commit them to your
  branch.
- As you update your PR and apply changes, mark each conversation as
  [resolved](https://docs.github.com/en/github/collaborating-with-issues-and-pull-requests/commenting-on-a-pull-request#resolving-conversations).
- If you run into any merge issues, checkout this
  [git tutorial](https://github.com/skills/resolve-merge-conflicts) to help you
  resolve merge conflicts and other issues.

### Your PR is merged!

Congratulations :tada::tada: The ds team thanks you :sparkles:.

Once your PR is merged, your contributions will be publicly visible on the next
release of ds and on [ds docs](https://sfm61319.github.io/ds/).

## Windows

This library can be developed on Windows, however a few potential gotchas need
to be kept in mind:

1. Toolchain: MSVC is the preferred compiler for Windows, which is installed in
   different locations for different versions of Visual Studio and Windows,
   and hence does not allow us to specify a fixed path for the compiler
   anywhere. It is therefore recommended to use
   [WSL2](https://learn.microsoft.com/en-us/windows/wsl/) for C/C++
   development, preferably with a debian-based distribution. If that is not
   possible, at least ensure that you are on the latest stable Windows and
   Visual Studio version.
2. Regular Expressions: Windows uses `\r\n` for line endings, while Unix-based
   systems use `\n`. Therefore, when working on Regular Expressions, use `\r?\n`
   instead of `\n` in order to support both environments. The Node.js
   [`os.EOL`](https://nodejs.org/api/os.html#os_os_eol) property can be used to
   get an OS-specific end-of-line marker.
3. Paths: Windows systems use `\` for the path separator, which would be
   returned by `path.join` and others. You could use `path.posix`,
   `path.posix.join` etc and the [slash](https://ghub.io/slash) module, if you
   need forward slashes - like for constructing URLs - or ensure your code works
   with either.
4. Filename too long error: There is a 260 character limit for a filename when
   Git is compiled with `msys`. While the suggestions below are not guaranteed
   to work and could cause other issues, a few workarounds include:
   - Update Git configuration: `git config --system core.longpaths true`
   - Consider using a different Git client on Windows
