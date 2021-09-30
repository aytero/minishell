# minishell
A simple Shell implementation.
\
\
**To launch:**
```
make && ./minishll
```
\
\
###Avaliable options
* Run an executable with arguments/options from absolute, relative or environment PATH
* Command history
* Builtin commands
	* echo [-n]
	* cd
	* pwd
	* export
	* unset
	* env
	* exit
* Redirections
	* <
	* \>
	* <<
	* \>>
* Pipes |
* Expanding environmental variables ($...)
* $? expands to most recent exit status
* Signals
	* ctrl-C
	* ctrl-D
	* ctrl-\
* " and ' syntax

