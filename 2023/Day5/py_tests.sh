cd src
#output=$(python3 solution.py)
echo "about to post the answer for $1 day $2..."
curl -X POST https://adventofcode.com/$1/day/$2/answer -H "Content-Type:application/x-www-form-urlencoded" --data-urlencode "level=2" --data-urlencode "answer=4524" -H "cookie: $3" -i -L -v -o response.html
cd ..