minigit - Tyler Renken's implementation

This program provides all of the functionality as specified in Phase 1 in the writeup

This is a basic version control program which works while it's running in a terminal window separate from the workspace.

With it, you can initialize a repository, similar to git, which will create a .minigit directory.
You can then add files to be tracked, remove files from tracking, commit versions of those files so that you may check them out later.
To do this, you must type 'add', 'remove', 'commit', or 'checkout' in lowercase. Do not add anything after the command.
The program will then ask for the necessary information to complete the operation,
either asking for the relative path name of the file you want to add or remove, or which commit you want to checkout.
To exit the program, type 'exit', or 'quit'. To display a message with a list of commands, type 'help'
