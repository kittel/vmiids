/*
 * Debug.h
 *
 *  Created on: Jun 8, 2010
 *      Author: kittel
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#ifdef VERBOSE

#include <stdio.h>

# define VERBOSE_FILE_POS__(line) " at " __FILE__ ":" #line
# define VERBOSE_FILE_POS_(line) VERBOSE_FILE_POS__(line)
# define VERBOSE_FILE_POS VERBOSE_FILE_POS_(__LINE__)

# define LIBVMI_ERROR(text) do { \
		printf("\n" VERBOSE ": " text "\n" "Error in %s" VERBOSE_FILE_POS, __PRETTY_FUNCTION__); \
		abort(); \
	} while (0)

# define LIBVMI_ASSERT(expr, msg, ...) do { \
		if (!(expr)) { \
			printf("\n" msg, ##__VA_ARGS__); \
			printf("\n" VERBOSE ": Assertion failed for " #expr \
					" in %s" VERBOSE_FILE_POS "\n", __PRETTY_FUNCTION__); \
			abort(); \
		} \
	} while (0)

#define LIBVMI_DEBUG_MSG(msg, ...) do { printf(VERBOSE ": " msg "\n", ##__VA_ARGS__); } while (0)
#define LIBVMI_DEBUG_MSG_N(msg, ...) do { printf(VERBOSE ": " msg, ##__VA_ARGS__); } while (0)

#define LIBVMI_WARN_MSG(msg, ...) do { printf(VERBOSE ": " msg "\n", ##__VA_ARGS__); printf("\n"); } while (0)

#else // !VERBOSE
#define LIBVMI_ERROR(text) do { abort(); } while (0)
#define LIBVMI_ASSERT(expr, msg, ...) do { if (!(expr)) {abort();} } while (0)
#define LIBVMI_DEBUG_MSG(msg, ...) do {} while (0)
#define LIBVMI_DEBUG_MSG_N(msg, ...) do {} while (0)
#define LIBVMI_WARN_MSG(msg, ...) do {} while (0)
#endif // !VERBOSE

#endif /* DEBUG_H_ */
