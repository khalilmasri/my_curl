## my_curl (similar to the UNIX command curl)
my_curl is a tool to get data from a server, using HTTP. The command is designed to work without user interaction.
#
### How does it work?

You send an url as parameter and it will print the html content of a web page.

![Screenshot](https://storage.googleapis.com/qwasar-public/s02_SE/network4_thumb_4_.png)

#### EXAMPLE
> ./my_curl http://www.columbia.edu/~fdc/sample.html
```HTML
> <!DOCTYPE HTML>
> <html lang="en">
> <head>
> ...
> <p>
> (End)
> <hr>
> </body>  <!-- close the <body> begun above -->
> </html>  <!-- close the <html> begun above -->
```

#
### How to run

1. `make` to Makefile.
2. You can run the command along with anywebsite you would like to curl from
    * > /my_curl http://www.columbia.edu/~fdc/sample.html
3. After you are done you can clean the Makefile
    * `make clean` to clean the objects
    * `make fclean` to clean the objects and the run file `./my_curl`
    * `make re` to `make clean` and `make fclean`
