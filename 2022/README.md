# Advent of Code 2022

The language of the year will be C++.

## Improvements from Previous Years

- [ ] [Automatically grab the problem and input from the website](#auto-fetch-problem-and-input)

## Auto Fetch Problem and Input

Making a `curl` request on the URL `https://adventofcode.com/{YEAR}/day/{DAY_NUM}/input` without logging in results in a request that demands a login code. 

Using the network inspector tool (`CTRL+SHIFT+I` in the web-browser), I found that the HTTP request header has a `cookie` field. I copied that field and used Postman to see if the request authentication was successful. It was, so I began to code up `run_test.sh` to automatically make these requests based on the day and save the problem input to a file.

I'm guessing the cookies only last so long, so I made a mechanism to enable changing the cookie. I also want to avoid pushing my cookie to a public GitHub if it means that people can log in to my account as me.