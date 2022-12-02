# Advent of Code 2022

The language of the year will be C++.

## Improvements from Previous Years

- [ ] [Automatically grab the problem and input from the website](#auto-fetch-problem-and-input)
- [ ] [Implementation of Google Tests](#implementation-of-google-tests)

## Auto Fetch Problem and Input

Making a `curl` request on the URL `https://adventofcode.com/{YEAR}/day/{DAY_NUM}/input` without logging in results in a request that demands a login code. 

Using the network inspector tool (`CTRL+SHIFT+I` in the web-browser), I found that the HTTP request header has a `cookie` field. I copied that field and used Postman to see if the request authentication was successful. It was, so I began to code up `run_test.sh` to automatically make these requests based on the day and save the problem input to a file.

I'm guessing the cookies only last so long, so I made a mechanism to enable changing the cookie. I also want to avoid pushing my cookie to a public GitHub if it means that people can log in to my account as me.

There was a request [on Reddit](https://www.reddit.com/r/adventofcode/comments/z9dhtd/please_include_your_contact_info_in_the_useragent/?utm_source=share&utm_medium=android_app&utm_name=androidcss&utm_term=1&utm_content=share_button) to add the GitHub page of the source code to the user-agent string of the API requests to filter out from spamming bots. I added this implementation with the `-A` flag in `curl`.

## Implementation of Google Tests

http://google.github.io/googletest/quickstart-cmake.html

in combination with 2021's `CMakeLists.txt` examples.