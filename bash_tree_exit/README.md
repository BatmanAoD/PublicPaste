# Problem description

Using `gnome-terminal`, attempts to turn a C++ program with an infinite loop
into a 'daemon' by disowning it FAIL, because the script closes when
`gnome-terminal` closes.

# StackOverflow links

 * [Explanation of `&`, `disown`, and `nohup`](http://superuser.com/a/178592/199803)
 * [Suggestion to use `sudo -b`](http://stackoverflow.com/a/19965862/1858225)
 * [Alternate approach I didn't try](http://stackoverflow.com/a/20338327/1858225)
       (sudo ... &)

# Successful approach

Use `sudo -b`
