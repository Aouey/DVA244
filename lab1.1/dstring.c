#include "dstring.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>


DString dstring_initialize(const char* str)
{
    assert(str != NULL);
	int lenOfStr = strlen(str);
    char* ptr = (char*)malloc(sizeof(char) * (lenOfStr + 1));
    if(ptr != NULL)
		strcpy(ptr, str);
    return ptr;
}

// Precondition: str ar ej NULL - testas med en assert
/* Tips:
   - Allokera (t.ex. med malloc) tillrackligt med minne for att fa plats med str,
	 glom inte att det maste finnas plats fšr \0 (nolltermineringen).
	 Glom inte att testa sa att allokeringen lyckades
   - Det Šr tillatet att anvŠnda inbyggda strangfunktioner (som t.ex strcpy())
   - Kom ihag att anvanda assert() */

   // Postcondition: returvardet innehaller samma strang som 'str' - behšver inte testas med assert

int dstring_concatenate(DString* destination, DString source)
{
    assert(destination != NULL);
    assert(*destination != NULL);
    assert(source != NULL);
    int destLen = strlen(*destination); int srcLen = strlen(source); char* temp = NULL;

    temp = (char*)realloc(*destination, (destLen + srcLen + 1) * sizeof(char));

    if (temp != NULL) {
        strcat(temp, source);
        *destination = temp;
        return 1;
    }
    return 0;
}

// Precondition: destination Šr ej NULL
// Precondition: *destination ar ej NULL
// Precondition: source ar ej NULL
// Preconditions testas med asserts.

/* Tips:
   - Tank pŒ att *destination redan ar en dynamiskt allokerad strang
   - Tank pŒ att vi kommer att behova allokera mer minne for att fa plats med den har langre strangen.
	 Minnet som *destination pekar pa behover utokas (realloc), hur stort ska det "nya" minnet bli?
	 Glom inte att nolltermineringen maste fa plats.
	 Nar du allokerar minne dynamiskt maste du alltid testa sa att allokeringen lyckades innan du
	 borjar jobba med minnet.
   - Det ar tillatet att anvanda inbyggda funktioner (som t.ex. strcat()).
*/
// Postcondition: *destination innehaller den gamla strangen ihopslagen med source - behšver inte testas med assert.

void dstring_truncate(DString* destination, unsigned int truncatedLength)
{
    assert(destination != NULL);
    assert(*destination != NULL);

    int destLen = strlen(*destination); char* temp = NULL;

    temp = (char*)malloc((destLen+1) * sizeof(char));

    if (temp == NULL || truncatedLength > destLen) {
    }
    else {
        strcpy(temp, *destination);
        temp[truncatedLength] = '\0';
        *destination = (char*)realloc(*destination, (truncatedLength+1) * sizeof(char));
        strcpy(*destination, temp);
        free(temp);
    }
}
// Precondition: destination Šr ej NULL, *destination ar ej NULL
// lŠngden (truncateLength) fŒr inte vara negativ
// Preconditions testas med asserts

/* Tips:
   - Anvand realloc for att frigora det overflodiga minnet
     (realloc frigor forst minnet och allokerar sedan nytt for den angivna storleken)
   - glom inte nolltermineringen
 Vad hŠnder om truncateLength Šr lŠngre Šn vad strŠngen Šr?*/

 // Postcondition: *destination ar inte langre an 'truncatedLength' tecken - behšver inte testas med assert

void dstring_print(DString str, FILE* textfile)
{
    assert(textfile != NULL);
    fprintf(textfile, "%s", str);
}
// Precondition: textfile ar inte NULL - maste testas innan du forsoker skriva till filen
/*Tank pŒ att filpekaren kopplas till filen innan funktionen anropas*/

/* filpekaren far inte stangas, filen ska fungera som vanligt efter anropet */
/*Den har funktionen ska vara generell, du ska kunna anvanda den for att skriva ut till
 en fil eller for att skriva ut i konsollen (pa skarmen). Om den anvands for att skriva till
 en extern fil sa kan du anta att filen oppnas och stangs innan respektive efter anrop till
 funktionen. Om den anvands for att skriva ut pa skarmen kan du anta att du far stdout till den
 andra parametern.
 Du ska inte skriva olika kod for att skriva till fil och till konsoll. Samma kod ska fungera for bada.*/

void dstring_delete(DString* stringToDelete)
{
    assert(stringToDelete != NULL);
    assert(*stringToDelete != NULL);
    free(*stringToDelete);
    *stringToDelete = NULL;
}
// Precondition: stringToDelete ar inte NULL

// Postcondition: *stringToDelete ar NULL och minnet ar frigjort - behšver inte testas med assert