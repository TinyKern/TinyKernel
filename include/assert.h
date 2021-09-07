#pragma once

#ifdef ASSERT
void assertion_failed(char *exp, char *file, char *base_file, int line);
# define Assert(exp)  if (exp) ; \
	else assertion_failed(#exp, __FILE__, __BASE_FILE__, __LINE__)
#else
# define Assert(exp)
#endif /* ASSERT */
