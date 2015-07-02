# ubuntupaste

ubuntupaste is a <b>micro plugin</b> written in <b>C</b> to enable cli-interface for <b>pastebin.ubuntu.com</b>.

![Screenshot](http://i.imgur.com/WC8Rqu6.png)

###Demo / Tutorial Video 
Here is a link to small demo / tutorial video https://vid.me/QlTB .If you still have any problems <b>create a Issue</b>

##Requirements
ubuntupaste is micro standalone plugin so it requires almost nothing.
 
 1. <b>gcc</b> to compile script / generate binary.

##Downloading
ubuntupaste can be directly downloaded from this repo by using <b>Git</b>.
```bash

  git clone https://github.com/flouthoc/ubuntupaste.git

```
<hr>

###Compiling
```bash
  gcc ubuntupaste.c -o ubuntupaste
```

###Usage
```bash
  ./ubuntupaste -t <syntax-type> -p <path-of-file>
```
####Help
<b> Get Usage Help </b>
```bash
  ./ubuntupaste -h
```

___

###About -t flag
<b>./ubuntupaste -t <syntax-type> </b>. t flag is used to specifiy the language type for which syntax highlighting will be done in yous paste script.

####Here is some of the -t flags
```bash
text - Plain Text
Cucumber - Gherkin
abap - ABAP
ada - Ada
ahk - autohotkey
antlr - ANTLR
antlr-as - ANTLR With ActionScript Target
antlr-cpp - ANTLR With CPP Target
antlr-csharp - ANTLR With C# Target
antlr-java - ANTLR With Java Target
antlr-objc - ANTLR With ObjectiveC Target
antlr-perl - ANTLR With Perl Target
antlr-python - ANTLR With Python Target
antlr-ruby - ANTLR With Ruby Target
apacheconf - ApacheConf
applescript - AppleScript
as - ActionScript
as3 - ActionScript 3
aspx-cs - aspx-cs
aspx-vb - aspx-vb
asy - Asymptote
basemake - Makefile
bash - Bash
bat - Batchfile
bbcode - BBCode
befunge - Befunge
blitzmax - BlitzMax
boo - Boo
c - C
c-objdump - c-objdump
cfm - Coldfusion HTML
cfs - cfstatement
cheetah - Cheetah
clojure - Clojure
cmake - CMake
coffee-script - CoffeeScript
common-lisp - Common Lisp
console - Bash Session
control - Debian Control file
cpp - C++
cpp-objdump - cpp-objdump
csharp - C#
css - CSS
css+django - CSS+Django/Jinja
css+erb - CSS+Ruby
css+genshitext - CSS+Genshi Text
css+mako - CSS+Mako
css+myghty - CSS+Myghty
css+php - CSS+PHP
css+smarty - CSS+Smarty
cython - Cython
d - D
d-objdump - d-objdump
delphi - Delphi
diff - Diff
django - Django/Jinja
dpatch - Darcs Patch
duel - Duel
dylan - Dylan
erb - ERB
erl - Erlang erl session
erlang - Erlang
evoque - Evoque
factor - Factor
felix - Felix
fortran - Fortran
gas - GAS
genshi - Genshi
genshitext - Genshi Text
glsl - GLSL
gnuplot - Gnuplot
go - Go
gooddata-cl - GoodData-CL
groff - Groff
haml - Haml
haskell - Haskell
html - HTML
html+cheetah - HTML+Cheetah
html+django - HTML+Django/Jinja
html+evoque - HTML+Evoque
html+genshi - HTML+Genshi
html+mako - HTML+Mako
html+myghty - HTML+Myghty
html+php - HTML+PHP
html+smarty - HTML+Smarty
html+velocity - HTML+Velocity
hx - haXe
hybris - Hybris
ini - INI
io - Io
ioke - Ioke
irc - IRC logs
jade - Jade
java - Java
js - JavaScript
js+cheetah - JavaScript+Cheetah
js+django - JavaScript+Django/Jinja
js+erb - JavaScript+Ruby
js+genshitext - JavaScript+Genshi Text
js+mako - JavaScript+Mako
js+myghty - JavaScript+Myghty
js+php - JavaScript+PHP
js+smarty - JavaScript+Smarty
jsp - Java Server Page
lhs - Literate Haskell
lighty - Lighttpd configuration file
llvm - LLVM
logtalk - Logtalk
lua - Lua
make - Makefile
mako - Mako
maql - MAQL
mason - Mason
matlab - Matlab
matlabsession - Matlab session
minid - MiniD
modelica - Modelica
modula2 - Modula-2
moocode - MOOCode
mupad - MuPAD
mxml - MXML
myghty - Myghty
mysql - MySQL
nasm - NASM
newspeak - Newspeak
nginx - Nginx configuration file
numpy - NumPy
objdump - objdump
objective-c - Objective-C
objective-j - Objective-J
ocaml - OCaml
ooc - Ooc
perl - Perl
php - PHP
postscript - PostScript
pot - Gettext Catalog
pov - POVRay
prolog - Prolog
properties - Properties
protobuf - Protocol Buffer
py3tb - Python 3.0 Traceback
pycon - Python console session
pytb - Python Traceback
python - Python
python3 - Python 3
ragel - Ragel
ragel-c - Ragel in C Host
ragel-cpp - Ragel in CPP Host
ragel-d - Ragel in D Host
ragel-em - Embedded Ragel
ragel-java - Ragel in Java Host
ragel-objc - Ragel in Objective C Host
ragel-ruby - Ragel in Ruby Host
raw - Raw token data
rb - Ruby
rbcon - Ruby irb session
rconsole - RConsole
rebol - REBOL
redcode - Redcode
rhtml - RHTML
rst - reStructuredText
sass - Sass
scala - Scala
scaml - Scaml
scheme - Scheme
scss - SCSS
smalltalk - Smalltalk
smarty - Smarty
sourceslist - Debian Sourcelist
splus - S
sql - SQL
sqlite3 - sqlite3con
squidconf - SquidConf
ssp - Scalate Server Page
tcl - Tcl
tcsh - Tcsh
tex - TeX
text - Text only
trac-wiki - MoinMoin/Trac Wiki markup
v - verilog
vala - Vala
vb.net - VB.net
velocity - Velocity
vim - VimL
xml - XML
xml+cheetah - XML+Cheetah
xml+django - XML+Django/Jinja
xml+erb - XML+Ruby
xml+evoque - XML+Evoque
xml+mako - XML+Mako
xml+myghty - XML+Myghty
xml+php - XML+PHP
xml+smarty - XML+Smarty
xml+velocity - XML+Velocity
xquery - XQuery
xslt - XSLT
yaml - YAML
```

#### However you can also get -t flag help in terminal
Use <b>-s</b> flag to get help about flags in terminal
```bash
  ./ubuntupaste -s
```
####About -p flag.
-p is used to specify path of your file like this <b> ./ubuntupaste -p <path-of-file </b>

##Lisense
BSD-2 Clause

##Contributing & Bugs
<b>Fork it , Create Pull</b>
####Contributing
  
  1. You can Optimize
  2. Clean the Code.
  3. Better Style
  4. You can add your own new features

###Bugs
I was lazy so could could be quite sloopy , so if you find out any bug <b>Just create an Issue</b>.

#####If you feel that plugin is good you can <b>Star</b> it so that i can put a debian package on my PPA for users to Direclty Install and use this thing

##Reference
This code uses a function to encode request before performing HTTP POST , function is <b>url_encode</b> which is written by <b> Fred </b> here (http://www.geekhideout.com/urlcode.shtml)




  


