#!/usr/bin/env bash
#
# Github Pages Updater
#
# This script jumps through the hoops needed to update the gh-pages branch.
# Always run it from the root source directory, like `scripts/updateghpages.sh`.
# Don't run this script while there are uncommitted changes. After the script
# exits Git will be on the master branch. This script always amends and force
# pushes (if requested), no useful history is kept. The other branches
# contain the actual history of the files used to generate the docs.
#

function restore()
{
	git checkout master || exit $?
	rm -f ./index.html ./index.html.tmp
}

# remove temp files and restore to master branch on exit
trap restore EXIT

# cleanup any lingering index.html so it doesn't clash with gh-pages
rm -f ./index.html || exit $?

# checkout the master branch so we're in a known branch
git checkout master || exit $?

# ensure the doc/index.html file is up-to-date
make html || exit $?

# copy the doc/index.html to a temp file
cp ./doc/index.html ./index.html.tmp || exit $?

# change to the gh-pages branch
git checkout gh-pages || exit $?

# move the temp file over the index.html that gh-pages branch has
mv ./index.html.tmp ./index.html || exit ?

# stage it (with --force since it's ignored)
git add --force ./index.html || exit $?

# commit with a generic message
git commit --amend -m "Update index.html for Github Pages" || exit $?

# ask if user wants to push to gh-pages branch to 'origin' remote
read -p "Do you want to push 'gh-pages' branch to origin? [y/N] " answer
case $answer in
	[Yy]* ) git push origin +gh-pages || exit $? ;;
	* )     ;;
esac
