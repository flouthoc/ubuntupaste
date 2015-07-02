/*---------------------------------------------------------------------------
** ubuntupaste.c
** Copyright BSD 3-Clause

** ubuntupaste
** A micro plugin to enable cli-interface for pastebin.ubntu.com
** Author: flouthoc (http:github.com/flouthoc)(flouthoc@gmail.com)
** <Contributors - Add Your Name Here >
** -------------------------------------------------------------------------*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <malloc.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>

#define panic(s) fputs(s,stdout)
#define FOUR_MB 4096
#define POSTER "UbuntuPaste"
#define SIZE_OF_POSTER 11
int debug_flag = 0;


void debug(char *);
void usage();
void printAbout();
void printTypes();
char to_hex(char ); 				/* Origin : http://www.geekhideout.com/urlcode.shtml **/
char *url_encode(char *);			/* Origin : http://www.geekhideout.com/urlcode.shtml **/
intmax_t sizeafterEncode(char *);


int main(int argc, char *argv[]){

	char *host = "paste.ubuntu.com";
	struct stat statBuffer;
	struct hostent *server;
	struct sockaddr_in serv_addr;
	int fd,total,written,recived,red,filefd,afterFormat,i;
	int port = 80;
	intmax_t fileSize;
	intmax_t sizepoor = 0;
	int sent = 0;
	char response[FOUR_MB + 1],ch;
	char *postData,*buffer,*postArgs;
	char requestFormat[] = "POST / HTTP/1.0\nContent-Type: application/x-www-form-urlencoded\nContent-Length: %d\n\n%s";
	char postargsFormat[] = "poster=%s&syntax=%s&content=";
	int option;
	char *type = NULL;
	char *path = NULL;
	opterr = 0;
	/**Command Line InterFace**/

	while((option = getopt(argc,argv,"auhst:p:")) != -1){

		switch(option){

			case 'u':
				usage();
				exit(1);
				break;

			case 's':
				printTypes();
				exit(1);
				break;

			case 'a':
				printAbout();
				exit(1);
				break;

			case 'h':
				usage();
				exit(1);
				break;

			case 't':
				type = optarg;
				break;

			case 'p':
				path = optarg;
				break;

			default:
				usage();
				exit(1);

		}
	}


	if(!(type && path)){

	 	usage();
	 	exit(1);
	}

	/** Command Line Inerface Ends **/

	postArgs = malloc( sizeof(postargsFormat) + SIZE_OF_POSTER + strlen(type) +  1);
	sprintf(postArgs,postargsFormat,POSTER,type);

	if((filefd = open(path, O_RDONLY, S_IRUSR)) < 0)
				perror("Unable to Open File");

	sizepoor = sizeafterEncode(path);
	if(fstat(filefd,&statBuffer)<0)
				perror("Unable to Stat File");

	fileSize = (intmax_t)(statBuffer.st_size);

	postData = malloc( (strlen(postArgs)+fileSize) + strlen(postArgs) + 1);
	sprintf(postData, requestFormat,(strlen(postArgs) + sizepoor),postArgs);
	total = strlen(postData);
	memset(response,0,sizeof(response));
	strcpy(response,postData);
	afterFormat = strlen(postData);


	buffer = response;
	debug("\n Creating Socket \n");

	fd = socket(AF_INET,SOCK_STREAM,0);
	if(fd<0)
		perror("Unable to Create Socket");

	debug("Resolving Server \n");

	server = gethostbyname(host);
	if(server == NULL)
		perror("Unable To Resolve paste.ubuntu.com");

	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	memcpy(&serv_addr.sin_addr.s_addr,server->h_addr,server->h_length);

	debug("Connecting to server \n");

	if(connect(fd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
		perror("Could not Connect To Ubuntu Server");

	debug("Performing Write \n");

	
	red = 0;

	while((red = read(filefd,&response[afterFormat], 1024)) > 0){

			response[afterFormat + red] = 0;
			strcpy(&response[afterFormat],url_encode(&response[afterFormat]));

			i = strlen(buffer);

			while(i > 0){

				if( (written = write(fd,buffer,i)) > 0){
						//total -= written;
						buffer += written;
						i -= written;
				}else{

					perror("Write Post Parameter");
				}
			}

			buffer = &response[afterFormat];
	}



	if(red < 0)
		perror("Unable to Read");


	memset(response,0,sizeof(response));
	total = sizeof(response) - 1;
	recived = 0;


	debug("Performing Read \n");

	while(recived < total){

		if( (written = read(fd,response,total)) > 0){

			recived += written;
			response + written;

		}else if(written == 0){

			break;
		}else{

			perror("Unable To Recive Response From Ubuntu Sever");
		}
	}


	debug("\nClosing Connection\n");

	close(fd);


	/** Parsing HTTP Response **/

	i = 0;
	buffer = NULL;
	memset(postData,0,strlen(postData));
	buffer = strtok(response, "\n");

    while (buffer) {

    	if( i == 1 ){

    		postData = malloc(strlen(buffer));
    		strcpy(postData,buffer);
    		printf("\nPaste Created Successfully on - %s\n",postData);
    	}


    	if( i == 5 ){

    		postData = malloc(strlen(buffer));
    		strcpy(postData,buffer);
    		printf("Here is the Link -  %s\n\n",postData);
    	}

    	buffer = strtok(NULL, "\n");
        i++;
    }
	
	return 0;

}


void debug(char *s){if(debug_flag){fputs(s,stdout);}}
void usage(){

	fputs("\nubuntupaste -t <syntax-type> -p <path-of-your-file>\n\n-s - To Get help about Syntax Type List \n-u - Usage \n-a - About Plugin & Author\n\n",stdout);
}


void printAbout(){

	fputs("\nUbuntuPaste (aka ubuntupaste)\n\nis a micro plugin which enables command line interface (cli-interface) for pastebin.ubuntu.com.Also ubuntupaste is open source plugin you can modify ,submit bug, add your features to its source on Github.Lisense Deailts on Github. \nAuthor : flouthoc (https://github.com/flouthoc) and Contributers\nSource : https://github.com/flouthoc/ubuntupaste\n\n",stdout);

}

void printTypes(){

	fputs("\n\n-t  Specifies the syntax type to enable syntax highlighting for that particular script \n\ntext - Plain Text\nCucumber - Gherkin\nabap - ABAP\nada - Ada\nahk - autohotkey\nantlr - ANTLR\nantlr-as - ANTLR With ActionScript Target\nantlr-cpp - ANTLR With CPP Target\nantlr-csharp - ANTLR With C# Target\nantlr-java - ANTLR With Java Target\nantlr-objc - ANTLR With ObjectiveC Target\nantlr-perl - ANTLR With Perl Target\nantlr-python - ANTLR With Python Target\nantlr-ruby - ANTLR With Ruby Target\napacheconf - ApacheConf\napplescript - AppleScript\nas - ActionScript\nas3 - ActionScript 3\naspx-cs - aspx-cs\naspx-vb - aspx-vb\nasy - Asymptote\nbasemake - Makefile\nbash - Bash\nbat - Batchfile\nbbcode - BBCode\nbefunge - Befunge\nblitzmax - BlitzMax\nboo - Boo\nc - C\nc-objdump - c-objdump\ncfm - Coldfusion HTML\ncfs - cfstatement\ncheetah - Cheetah\nclojure - Clojure\ncmake - CMake\ncoffee-script - CoffeeScript\ncommon-lisp - Common Lisp\nconsole - Bash Session\ncontrol - Debian Control file\ncpp - C++\ncpp-objdump - cpp-objdump\ncsharp - C#\ncss - CSS\ncss+django - CSS+Django/Jinja\ncss+erb - CSS+Ruby\ncss+genshitext - CSS+Genshi Text\ncss+mako - CSS+Mako\ncss+myghty - CSS+Myghty\ncss+php - CSS+PHP\ncss+smarty - CSS+Smarty\ncython - Cython\nd - D\nd-objdump - d-objdump\ndelphi - Delphi\ndiff - Diff\ndjango - Django/Jinja\ndpatch - Darcs Patch\nduel - Duel\ndylan - Dylan\nerb - ERB\nerl - Erlang erl session\nerlang - Erlang\nevoque - Evoque\nfactor - Factor\nfelix - Felix\nfortran - Fortran\ngas - GAS\ngenshi - Genshi\ngenshitext - Genshi Text\nglsl - GLSL\ngnuplot - Gnuplot\ngo - Go\ngooddata-cl - GoodData-CL\ngroff - Groff\nhaml - Haml\nhaskell - Haskell\nhtml - HTML\nhtml+cheetah - HTML+Cheetah\nhtml+django - HTML+Django/Jinja\nhtml+evoque - HTML+Evoque\nhtml+genshi - HTML+Genshi\nhtml+mako - HTML+Mako\nhtml+myghty - HTML+Myghty\nhtml+php - HTML+PHP\nhtml+smarty - HTML+Smarty\nhtml+velocity - HTML+Velocity\nhx - haXe\nhybris - Hybris\nini - INI\nio - Io\nioke - Ioke\nirc - IRC logs\njade - Jade\njava - Java\njs - JavaScript\njs+cheetah - JavaScript+Cheetah\njs+django - JavaScript+Django/Jinja\njs+erb - JavaScript+Ruby\njs+genshitext - JavaScript+Genshi Text\njs+mako - JavaScript+Mako\njs+myghty - JavaScript+Myghty\njs+php - JavaScript+PHP\njs+smarty - JavaScript+Smarty\njsp - Java Server Page\nlhs - Literate Haskell\nlighty - Lighttpd configuration file\nllvm - LLVM\nlogtalk - Logtalk\nlua - Lua\nmake - Makefile\nmako - Mako\nmaql - MAQL\nmason - Mason\nmatlab - Matlab\nmatlabsession - Matlab session\nminid - MiniD\nmodelica - Modelica\nmodula2 - Modula-2\nmoocode - MOOCode\nmupad - MuPAD\nmxml - MXML\nmyghty - Myghty\nmysql - MySQL\nnasm - NASM\nnewspeak - Newspeak\nnginx - Nginx configuration file\nnumpy - NumPy\nobjdump - objdump\nobjective-c - Objective-C\nobjective-j - Objective-J\nocaml - OCaml\nooc - Ooc\nperl - Perl\nphp - PHP\npostscript - PostScript\npot - Gettext Catalog\npov - POVRay\nprolog - Prolog\nproperties - Properties\nprotobuf - Protocol Buffer\npy3tb - Python 3.0 Traceback\npycon - Python console session\npytb - Python Traceback\npython - Python\npython3 - Python 3\nragel - Ragel\nragel-c - Ragel in C Host\nragel-cpp - Ragel in CPP Host\nragel-d - Ragel in D Host\nragel-em - Embedded Ragel\nragel-java - Ragel in Java Host\nragel-objc - Ragel in Objective C Host\nragel-ruby - Ragel in Ruby Host\nraw - Raw token data\nrb - Ruby\nrbcon - Ruby irb session\nrconsole - RConsole\nrebol - REBOL\nredcode - Redcode\nrhtml - RHTML\nrst - reStructuredText\nsass - Sass\nscala - Scala\nscaml - Scaml\nscheme - Scheme\nscss - SCSS\nsmalltalk - Smalltalk\nsmarty - Smarty\nsourceslist - Debian Sourcelist\nsplus - S\nsql - SQL\nsqlite3 - sqlite3con\nsquidconf - SquidConf\nssp - Scalate Server Page\ntcl - Tcl\ntcsh - Tcsh\ntex - TeX\ntext - Text only\ntrac-wiki - MoinMoin/Trac Wiki markup\nv - verilog\nvala - Vala\nvb.net - VB.net\nvelocity - Velocity\nvim - VimL\nxml - XML\nxml+cheetah - XML+Cheetah\nxml+django - XML+Django/Jinja\nxml+erb - XML+Ruby\nxml+evoque - XML+Evoque\nxml+mako - XML+Mako\nxml+myghty - XML+Myghty\nxml+php - XML+PHP\nxml+smarty - XML+Smarty\nxml+velocity - XML+Velocity\nxquery - XQuery\nxslt - XSLT\nyaml - YAML\n",stdout);
}

/* Converts an integer value to its hex character*/
char to_hex(char code) {

	/** source : http://www.geekhideout.com/urlcode.shtml **/

  static char hex[] = "0123456789abcdef";
  return hex[code & 15];
}

/* Returns a url-encoded version of str */
/* IMPORTANT: be sure to free() the returned string after use */
char *url_encode(char *str) {

	/** source : http://www.geekhideout.com/urlcode.shtml **/
int a = 0;
char *pstr = str, *buf = malloc(strlen(str) * 3 + 1), *pbuf = buf;
	  while (*pstr) {

		    if (isalnum(*pstr) || *pstr == '-' || *pstr == '_' || *pstr == '.' || *pstr == '~')
		      *pbuf++ = *pstr;
		    else if (*pstr == ' ')
		      *pbuf++ = '+';
		    else
		      *pbuf++ = '%', *pbuf++ = to_hex(*pstr >> 4), *pbuf++ = to_hex(*pstr & 15);
		    pstr++;

	  }
	  pbuf -= 3;
	  *pbuf = 0;
	  return buf;
}



intmax_t sizeafterEncode(char *path){

	int red;
	int fd;
	intmax_t size = 0;
	char rep[1050];
	char *buffer;

	if((fd = open(path, O_RDONLY, S_IRUSR)) < 0)
				perror("Unable to Open File");

	while((red = read(fd,rep, 1024)) > 0){

		rep[red] = 0;
		buffer = url_encode(rep);
		size += strlen(buffer);
		free(buffer);
	}

	if(red < 0)
		perror("While Calculating encoded format");


	close(fd);
	return size;
}



