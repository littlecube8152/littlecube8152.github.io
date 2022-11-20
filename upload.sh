cd C:\\Hugo\\Sites\\github.io 
hugo -D
git init
git add .
timestr=$(date +"%Y-%m-%d %T")
git commit -m "$1, auto uploaded on $timestr" 
# git pull --rebase origin master
# When updated something and the github seems buggy, do this to rebase.
git push -u origin master
read -p "Press enter to continue"