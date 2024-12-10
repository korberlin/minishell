#include "minishell.h"

void print_welcome(void)
{
    printf(GREEN "ooo        ooooo  o8o               o8o           oooo                  oooo  oooo  \n" RESET);
    printf(GREEN "`88.       .888'  `\"'               `\"'           `888                  `888  `888  \n" RESET);
    printf(GREEN " 888b     d'888  oooo  ooo. .oo.   oooo   .oooo.o  888 .oo.    .ooooo.   888   888  \n" RESET);
    printf(GREEN " 8 Y88. .P  888  `888  `888P\"Y88b  `888  d88(  \"8  888P\"Y88b  d88' `88b  888   888  \n" RESET);
    printf(GREEN " 8  `888'   888   888   888   888   888  `\"Y88b.   888   888  888ooo888  888   888  \n" RESET);
    printf(GREEN " 8    Y     888   888   888   888   888  o.  )88b  888   888  888    .o  888   888  \n" RESET);
    printf(GREEN "o8o        o888o o888o o888o o888o o888o 8\"\"888P' o888o o888o `Y8bod8P' o888o o888o \n" RESET);
    printf(GREEN "                                                                                     \n" RESET);
    printf(GREEN "                                                                                     \n" RESET);

    printf(YELLOW "\nWelcome to Minishell! Your personalized shell.\n" RESET);
    printf(YELLOW "Type commands and explore. Type 'exit' to quit.\n\n" RESET);
    printf(CYAN "This shell has been made by:\n" RESET);
    printf(CYAN " - Görkem Köksal\n" RESET);
    printf(CYAN " - Aziz Ateş Sönmez\n\n" RESET);
}