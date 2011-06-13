#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#else
#include <strings.h>
#endif

#include "internal.h"
#include "die.h"
#include "strlimcpy.h"
#include "token.h"
#include "scala_res.h"

#define MAXCOMPLETENAME 1024 /* max size of complete name of class */
#define MAXCLASSSTACK 100 /* max size of class stack */

void
scala(const struct parser_param *param)
{
	int c;
	int level;
	const char *interested = NULL;

	if (!opentoken(param->file))
		die("'%s' cannot open.", param->file);
	while ((c = nexttoken(interested, scala_reserved_word)) != EOF) {
		switch (c) {
		case SYMBOL:
			PUT(PARSER_REF_SYM, token, lineno, sp);
			break;

		case SCALA_VAL:
		case SCALA_VAR:
		case SCALA_DEF:
		case SCALA_CLASS:
		case SCALA_OBJECT:
		case SCALA_TRAIT:
			if ((c = nexttoken(interested, scala_reserved_word)) == SYMBOL) {
				PUT(PARSER_DEF, token, lineno, sp);
			}
			break;

		default:
			break;
		}
	}
	closetoken();
}
