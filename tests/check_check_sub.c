#include "../lib/libcompat.h"

#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#include <check.h>
#include "check_check.h"

#define _STR(Y) #Y


START_TEST(test_lno)
{
  ck_abort_msg("Failure expected");
  #define LINENO_lno _STR(__LINE__)
}
END_TEST

START_TEST(test_mark_lno)
{
  mark_point();
  #define LINENO_mark_lno _STR(__LINE__)
#ifdef _POSIX_VERSION
  exit(EXIT_FAILURE); /* should fail with mark_point above as line */
#endif /* _POSIX_VERSION */
}

END_TEST
START_TEST(test_pass)
{
  ck_assert_msg(1 == 1, "This test should pass");
  ck_assert_msg(9999, "This test should pass");
}
END_TEST

START_TEST(test_fail_unless)
{
  fail_unless(1 == 2, "This test should fail");
}
END_TEST

START_TEST(test_fail_if_pass)
{
  fail_if(1 == 2, "This test should pass");
  fail_if(0, "This test should pass");
}
END_TEST

START_TEST(test_fail_if_fail)
{
  fail_if(1 == 1, "This test should fail");
}
END_TEST

START_TEST(test_fail_null_msg)
{
  fail_unless(2 == 3, NULL);
}
END_TEST

#if defined(__GNUC__)
START_TEST(test_fail_no_msg)
{ /* taking out the NULL provokes an ISO C99 warning in GCC */
  fail_unless(4 == 5, NULL);
}
END_TEST
#endif /* __GNUC__ */
START_TEST(test_fail_if_null_msg)
{
  fail_if(2 != 3, NULL);
}
END_TEST

#if defined(__GNUC__)
START_TEST(test_fail_if_no_msg)
{ /* taking out the NULL provokes an ISO C99 warning in GCC */
  fail_if(4 != 5, NULL);
}
END_TEST
#endif /* __GNUC__ */
START_TEST(test_fail_vararg_msg_1)
{
  int x = 3;
  int y = 4;
  fail_unless(x == y, "%d != %d", x, y);
}
END_TEST

START_TEST(test_fail_vararg_msg_2)
{
  int x = 5;
  int y = 6;
  fail_if(x != y, "%d != %d", x, y);
}
END_TEST

START_TEST(test_fail_vararg_msg_3)
{
  int x = 7;
  int y = 7;
  fail("%d == %d", x, y);
}
END_TEST

#if defined(__GNUC__)
START_TEST(test_fail_empty)
{ /* plain fail() doesn't compile with xlc in C mode because of `, ## __VA_ARGS__' problem */
  /* on the other hand, taking out the NULL provokes an ISO C99 warning in GCC */
  fail(NULL);
}
END_TEST
#endif /* __GNUC__ */

START_TEST(test_ck_abort)
{
  ck_abort();
  #define LINENO_ck_abort _STR(__LINE__)
}
END_TEST

START_TEST(test_ck_abort_msg)
{
  ck_abort_msg("Failure expected");
  #define LINENO_ck_abort_msg _STR(__LINE__)
}
END_TEST

/* FIXME: perhaps passing NULL to ck_abort_msg should be an error. */
START_TEST(test_ck_abort_msg_null)
{
  ck_abort_msg(NULL);
  #define LINENO_ck_abort_msg_null _STR(__LINE__)
}
END_TEST

/* These ck_assert tests are all designed to fail on the last
   assertion. */

START_TEST(test_ck_assert)
{
  int x = 3;
  int y = 3;
  ck_assert(1);
  ck_assert(x == y);
  y++;
  ck_assert(x != y);
  ck_assert(x == y);
  #define LINENO_ck_assert _STR(__LINE__)
}
END_TEST

START_TEST(test_ck_assert_null)
{
  ck_assert(0);
  #define LINENO_ck_assert_null _STR(__LINE__)
}
END_TEST

START_TEST(test_ck_assert_int_eq)
{
  int x = 3;
  int y = 3;
  ck_assert_int_eq(x, y);
  y++;
  ck_assert_int_eq(x, y);
  #define LINENO_ck_assert_int_eq _STR(__LINE__)
}
END_TEST

START_TEST(test_ck_assert_int_ne)
{
  int x = 3;
  int y = 2;
  ck_assert_int_ne(x, y);
  y++;
  ck_assert_int_ne(x, y);
  #define LINENO_ck_assert_int_ne _STR(__LINE__)
}
END_TEST

START_TEST(test_ck_assert_int_lt)
{
  int x = 2;
  int y = 3;
  ck_assert_int_lt(x, y);
  ck_assert_int_lt(x, x);
  #define LINENO_ck_assert_int_lt _STR(__LINE__)
}
END_TEST

START_TEST(test_ck_assert_int_le)
{
  int x = 2;
  int y = 3;
  ck_assert_int_le(x, y);
  ck_assert_int_le(x, x);
  ck_assert_int_le(y, x);
  #define LINENO_ck_assert_int_le _STR(__LINE__)
}
END_TEST

START_TEST(test_ck_assert_int_gt)
{
  int x = 2;
  int y = 3;
  ck_assert_int_gt(y, x);
  ck_assert_int_gt(y, y);
  #define LINENO_ck_assert_int_gt _STR(__LINE__)
}
END_TEST

START_TEST(test_ck_assert_int_ge)
{
  int x = 2;
  int y = 3;
  ck_assert_int_ge(y, x);
  ck_assert_int_ge(y, x);
  ck_assert_int_ge(x, y);
  #define LINENO_ck_assert_int_ge _STR(__LINE__)
}
END_TEST

START_TEST(test_ck_assert_int_expr)
{
  int x = 1;
  int y = 0;
  ck_assert_int_eq(x, ++y);
  ck_assert_int_eq(x, y);
  #define LINENO_ck_assert_int_expr _STR(__LINE__)
} END_TEST

START_TEST(test_ck_assert_uint_eq)
{
  unsigned int x = 3;
  unsigned int y = 3;
  ck_assert_uint_eq(x, y);
  y++;
  ck_assert_uint_eq(x, y);
  #define LINENO_ck_assert_uint_eq _STR(__LINE__)
}
END_TEST

START_TEST(test_ck_assert_uint_ne)
{
  unsigned int x = 3;
  unsigned int y = 2;
  ck_assert_uint_ne(x, y);
  y++;
  ck_assert_uint_ne(x, y);
  #define LINENO_ck_assert_uint_ne _STR(__LINE__)
}
END_TEST

START_TEST(test_ck_assert_uint_lt)
{
  unsigned int x = 2;
  unsigned int y = 3;
  ck_assert_uint_lt(x, y);
  ck_assert_uint_lt(x, x);
  #define LINENO_ck_assert_uint_lt _STR(__LINE__)
}
END_TEST

START_TEST(test_ck_assert_uint_le)
{
  unsigned int x = 2;
  unsigned int y = 3;
  ck_assert_uint_le(x, y);
  ck_assert_uint_le(x, x);
  ck_assert_uint_le(y, x);
  #define LINENO_ck_assert_uint_le _STR(__LINE__)
}
END_TEST

START_TEST(test_ck_assert_uint_gt)
{
  unsigned int x = 2;
  unsigned int y = 3;
  ck_assert_uint_gt(y, x);
  ck_assert_uint_gt(y, y);
  #define LINENO_ck_assert_uint_gt _STR(__LINE__)
}
END_TEST

START_TEST(test_ck_assert_uint_ge)
{
  unsigned int x = 2;
  unsigned int y = 3;
  ck_assert_uint_ge(y, x);
  ck_assert_uint_ge(y, x);
  ck_assert_uint_ge(x, y);
  #define LINENO_ck_assert_uint_ge _STR(__LINE__)
}
END_TEST

START_TEST(test_ck_assert_uint_expr)
{
  unsigned int x = 1;
  unsigned int y = 0;
  ck_assert_uint_eq(x, ++y);
  ck_assert_uint_eq(x, y);
  #define LINENO_ck_assert_uint_expr _STR(__LINE__)
} END_TEST

START_TEST(test_ck_assert_str_eq)
{
  const char *s = "test2";
  ck_assert_str_eq("test2", s);
  ck_assert_str_eq("test1", s);
  #define LINENO_ck_assert_str_eq _STR(__LINE__)
}
END_TEST

START_TEST(test_ck_assert_str_ne)
{
  const char *s = "test2";
  const char *t = "test1";
  ck_assert_str_ne(t, s);
  t = "test2";
  ck_assert_str_ne(t, s);
  #define LINENO_ck_assert_str_ne _STR(__LINE__)
}
END_TEST

START_TEST(test_ck_assert_str_lt)
{
  const char *s = "test1";
  const char *t = "test2";
  ck_assert_str_lt(s, t);
  ck_assert_str_lt(s, s);
  #define LINENO_ck_assert_str_lt _STR(__LINE__)
}
END_TEST

START_TEST(test_ck_assert_str_le)
{
  const char *s = "test1";
  const char *t = "test2";
  ck_assert_str_le(s, t);
  ck_assert_str_le(s, s);
  ck_assert_str_le(t, s);
  #define LINENO_ck_assert_str_le _STR(__LINE__)
}
END_TEST

START_TEST(test_ck_assert_str_gt)
{
  const char *s = "test1";
  const char *t = "test2";
  ck_assert_str_gt(t, s);
  ck_assert_str_gt(t, t);
  #define LINENO_ck_assert_str_gt _STR(__LINE__)
}
END_TEST

START_TEST(test_ck_assert_str_ge)
{
  const char *s = "test1";
  const char *t = "test2";
  ck_assert_str_ge(t, s);
  ck_assert_str_ge(t, t);
  ck_assert_str_ge(s, t);
  #define LINENO_ck_assert_str_ge _STR(__LINE__)
}
END_TEST

START_TEST(test_ck_assert_str_expr)
{
  const char *s = "test1";
  const char *t[] = { "test1", "test2" };
  int i = -1;
  ck_assert_str_eq(s, t[++i]);
  ck_assert_str_eq(s, t[i]);
  #define LINENO_ck_assert_str_expr _STR(__LINE__)
}
END_TEST

START_TEST(test_ck_assert_ptr_eq)
{
  int * x = (int*)0x1;
  int * y = (int*)0x2;
  ck_assert_ptr_eq(NULL, NULL);
  ck_assert_ptr_eq(x,    x);
  ck_assert_ptr_eq(x,    y);
  #define LINENO_ck_assert_ptr_eq _STR(__LINE__)
}
END_TEST

START_TEST(test_ck_assert_ptr_ne)
{
  int * x = (int*)0x1;
  int * y = (int*)0x2;
  int * z = x;
  ck_assert_ptr_ne(x,    y);
  ck_assert_ptr_ne(x,    NULL);
  ck_assert_ptr_ne(NULL, y);
  ck_assert_ptr_ne(x,    z);
  #define LINENO_ck_assert_ptr_ne _STR(__LINE__)
}
END_TEST

START_TEST(test_segv)
  #define LINENO_segv _STR(__LINE__)
{
  raise (SIGSEGV);
}
END_TEST


START_TEST(test_fpe)
{
  raise (SIGFPE);
}
END_TEST

/* TODO:
   unit test running the same suite in succession */

START_TEST(test_mark_point)
{
  int i;
  i = 0;
  i++;
  mark_point();
  raise(SIGFPE);
  ck_abort_msg("Shouldn't reach here");
}
END_TEST

#if TIMEOUT_TESTS_ENABLED
START_TEST(test_eternal)
  #define LINENO_eternal _STR(__LINE__)
{
  for (;;)
    ;
}
END_TEST

/* 
 * Only include sub-second timing tests on systems
 * that support librt.
 */
#ifdef HAVE_LIBRT
START_TEST(test_sleep0_025)
  #define LINENO_sleep0_025 _STR(__LINE__)
{
  usleep(25*1000);
}
END_TEST

START_TEST(test_sleep1)
  #define LINENO_sleep1 _STR(__LINE__)
{
  sleep(1);
}
END_TEST
#endif /* HAVE_LIBRT */

START_TEST(test_sleep2)
  #define LINENO_sleep2 _STR(__LINE__)
{
  sleep(2);
}
END_TEST

START_TEST(test_sleep5)
  #define LINENO_sleep5 _STR(__LINE__)
{
  sleep(5);
}
END_TEST

START_TEST(test_sleep9)
  #define LINENO_sleep9 _STR(__LINE__)
{
  sleep(9);
}
END_TEST

START_TEST(test_sleep14)
  #define LINENO_sleep14 _STR(__LINE__)
{
  sleep(14);
}
END_TEST
#endif

START_TEST(test_early_exit)
{
  exit(EXIT_FAILURE);
}
END_TEST

START_TEST(test_null)
{  
  Suite *s;
  TCase *tc;
  
  s = suite_create(NULL);
  tc = tcase_create(NULL);
  suite_add_tcase (s, NULL);
  tcase_add_test (tc, NULL);
  srunner_free(srunner_create(NULL));
  srunner_run_all (NULL, -1);
  srunner_free (NULL);
  ck_abort_msg("Completed properly");
}
END_TEST

START_TEST(test_null_2)
{
  SRunner *sr = srunner_create(NULL);
  srunner_run_all (sr, CK_NORMAL);
  srunner_free (sr);
  ck_abort_msg("Completed properly");
}
END_TEST

#ifdef _POSIX_VERSION
START_TEST(test_fork1p_pass)
{
  pid_t pid;

  if((pid = fork()) < 0) {
    ck_abort_msg("Failed to fork new process");
  } else if (pid > 0) {
    ck_assert_msg(1, NULL);
    kill(pid, SIGKILL);
  } else {
    for (;;) {
      sleep(1);
    }
  }
}
END_TEST

START_TEST(test_fork1p_fail)
{
  pid_t pid;
  
  if((pid = fork()) < 0) {
    ck_abort_msg("Failed to fork new process");
  } else if (pid > 0) {
    ck_abort_msg("Expected fail");
    kill(pid, SIGKILL);
  } else {
    for (;;) {
      sleep(1);
    }
  }
}
END_TEST

START_TEST(test_fork1c_pass)
{
  pid_t pid;
  
  if((pid = check_fork()) < 0) {
    ck_abort_msg("Failed to fork new process");
  } else if (pid > 0) {
    check_waitpid_and_exit(pid);
  } else {
    ck_assert_msg(1, NULL);
    check_waitpid_and_exit(0);
  }
}
END_TEST

START_TEST(test_fork1c_fail)
{
  pid_t pid;
  
  if((pid = check_fork()) < 0) {
    ck_abort_msg("Failed to fork new process");
  } else if (pid == 0) {
    ck_abort_msg("Expected fail");
    check_waitpid_and_exit(0);
  }
  check_waitpid_and_exit(pid);
}
END_TEST

START_TEST(test_fork2_pass)
{
  pid_t pid;
  pid_t pid2;
  
  if((pid = check_fork()) < 0) {
    ck_abort_msg("Failed to fork new process");
  } else if (pid > 0) {
    if((pid2 = check_fork()) < 0) {
      ck_abort_msg("Failed to fork new process");
    } else if (pid2 == 0) {
      ck_assert_msg(1, NULL);
      check_waitpid_and_exit(0);
    }
    check_waitpid_and_exit(pid2);
  }
  check_waitpid_and_exit(pid);
}
END_TEST

START_TEST(test_fork2_fail)
{
  pid_t pid;
  pid_t pid2;
  
  if((pid = check_fork()) < 0) {
    ck_abort_msg("Failed to fork new process");
  } else if (pid > 0) {
    if((pid2 = check_fork()) < 0) {
      ck_abort_msg("Failed to fork new process");
    } else if (pid2 == 0) {
      ck_abort_msg("Expected fail");
      check_waitpid_and_exit(0);
    }
    check_waitpid_and_exit(pid2);
    ck_abort_msg("Expected fail");
  }
  check_waitpid_and_exit(pid);
}
END_TEST
#endif /* _POSIX_VERSION */

START_TEST(test_srunner)
{
  Suite *s;
  SRunner *sr;

  s = suite_create("Check Servant3");
  ck_assert_msg(s != NULL, NULL);
  sr = srunner_create(NULL);
  ck_assert_msg(sr != NULL, NULL);
  srunner_add_suite(sr, s);
  srunner_free(sr);

  sr = srunner_create(NULL);
  ck_assert_msg(sr != NULL, NULL);
  srunner_add_suite(sr, NULL);
  srunner_free(sr);

  s = suite_create("Check Servant3");
  ck_assert_msg(s != NULL, NULL);
  sr = srunner_create(s);
  ck_assert_msg(sr != NULL, NULL);
  srunner_free(sr);
}
END_TEST

START_TEST(test_2nd_suite)
{
  ck_abort_msg("We failed");
}
END_TEST

Suite *make_sub2_suite(void)
{
  Suite *s = suite_create("Check Servant2");
  TCase *tc = tcase_create("Core");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_srunner);
  tcase_add_test(tc, test_2nd_suite);

  return s;
}

void init_master_tests_lineno(int num_master_tests) {
  const char * lineno[] = {
/* Simple Tests */
    LINENO_lno,
    LINENO_mark_lno,
    "-1",
    "-1",
    "-1",
    "-1",
    "-1",
    "-1",
    "-1",
    "-1",
    "-1",
    "-1",
    "-1",
    "-1",
    LINENO_ck_abort,
    LINENO_ck_abort_msg,
    LINENO_ck_abort_msg_null,
    LINENO_ck_assert,
    LINENO_ck_assert_null,
    LINENO_ck_assert_int_eq,
    LINENO_ck_assert_int_eq,
    LINENO_ck_assert_int_ne,
    LINENO_ck_assert_int_lt,
    LINENO_ck_assert_int_le,
    LINENO_ck_assert_int_gt,
    LINENO_ck_assert_int_ge,
    LINENO_ck_assert_int_expr,
    LINENO_ck_assert_uint_ne,
    LINENO_ck_assert_uint_lt,
    LINENO_ck_assert_uint_le,
    LINENO_ck_assert_uint_gt,
    LINENO_ck_assert_uint_ge,
    LINENO_ck_assert_uint_expr,
    LINENO_ck_assert_str_eq,
    LINENO_ck_assert_str_ne,
    LINENO_ck_assert_str_lt,
    LINENO_ck_assert_str_le,
    LINENO_ck_assert_str_gt,
    LINENO_ck_assert_str_ge,
    LINENO_ck_assert_str_expr,
    LINENO_ck_assert_ptr_eq,
    LINENO_ck_assert_ptr_ne,

/* Signal Tests */
    "-1",
    "-1",
    LINENO_segv,
    "-1",
    "-1",
    "-1",
    "-1",

#if TIMEOUT_TESTS_ENABLED
#if HAVE_WORKING_SETENV
/* Environment Integer Timeout Tests */
    LINENO_eternal,
    "-1",
    "-1",
    LINENO_sleep9,
/* Environment Double Timeout Tests */
    LINENO_eternal,
#ifdef HAVE_LIBRT
    "-1",
    LINENO_sleep1,
#endif /* HAVE_LIBRT */
    LINENO_sleep2,
    LINENO_sleep5,
    LINENO_sleep9,
#endif
/* Default Timeout Tests */
    LINENO_eternal,
#ifdef HAVE_LIBRT
    "-1",
    "-1",
#endif /* HAVE_LIBRT */
    "-1",
    LINENO_sleep5,
    LINENO_sleep9,
/* User Integer Timeout Tests */
    LINENO_eternal,
    "-1",
    "-1",
    LINENO_sleep9,
/* User Double Timeout Tests */
    LINENO_eternal,
#ifdef HAVE_LIBRT
    "-1",
    LINENO_sleep1,
#endif /* HAVE_LIBRT */
    LINENO_sleep2,
    LINENO_sleep5,
    LINENO_sleep9,
    
/* Default Timeout Tests (again)*/
    LINENO_eternal,
#ifdef HAVE_LIBRT
    "-1",
    "-1",
#endif /* HAVE_LIBRT */
    "-1",
    LINENO_sleep5,
    LINENO_sleep9,
#if HAVE_WORKING_SETENV
/* Environment Integer Timeout Scaling Tests */
    LINENO_eternal,
#ifdef HAVE_LIBRT
    "-1",
    "-1",
#endif /* HAVE_LIBRT */
    "-1",
    "-1",
    "-1",
    LINENO_sleep14,
/* Environment Double Timeout Scaling Tests */
    LINENO_eternal,
#ifdef HAVE_LIBRT
    "-1",
    LINENO_sleep1,
#endif /* HAVE_LIBRT */
    LINENO_sleep2,
    LINENO_sleep5,
    LINENO_sleep9,
    LINENO_sleep14,
/* Timeout Integer Scaling Tests */
    LINENO_eternal,
#ifdef HAVE_LIBRT
    "-1",
    "-1",
    "-1",
#endif /* HAVE_LIBRT */
    "-1",
    LINENO_sleep9,
/* Timeout Double Scaling Tests */
    LINENO_eternal,
#ifdef HAVE_LIBRT
    "-1",
    "-1",
#endif /* HAVE_LIBRT */
    LINENO_sleep2,
    LINENO_sleep5,
    LINENO_sleep9,
/* User Integer Timeout Scaling Tests */
    LINENO_eternal,
#ifdef HAVE_LIBRT
    "-1",
    "-1",
#endif /* HAVE_LIBRT */
    "-1",
    "-1",
    "-1",
    LINENO_sleep14,
/* User Integer Timeout Scaling Tests */
    LINENO_eternal,
#ifdef HAVE_LIBRT
    "-1",
    LINENO_sleep1,
#endif /* HAVE_LIBRT */
    LINENO_sleep2,
    LINENO_sleep5,
    LINENO_sleep9,
    LINENO_sleep14,
#endif
#endif

/* Limit Tests */
    "-1",
    "-1",
    "-1",

/* Msg and fork Tests */
    "-1",
    "-1",
    "-1",
    "-1",
    "-1",
    "-1",

/* Core */
    "-1",
    "-1"
  };
  int s = sizeof lineno /sizeof lineno[0];
  int i;
  
  if(s != num_master_tests)
  {
    fprintf(stderr, "Error: The number of line numbers (%d) does not match the number of tests (%d)\n",
      s, num_master_tests);
    exit(1);
  }

  for (i = 0; i < s; i++) {
    master_tests_lineno[i] = atoi(lineno[i]) - 1;
  }
}

Suite *make_sub_suite(void)
{
  Suite *s;

  TCase *tc_simple;
  TCase *tc_signal;
#if TIMEOUT_TESTS_ENABLED
#if HAVE_WORKING_SETENV
  TCase *tc_timeout_env_int;
  TCase *tc_timeout_env_double;
#endif /* HAVE_WORKING_SETENV */
  TCase *tc_timeout_default;
  TCase *tc_timeout_usr_int;
  TCase *tc_timeout_usr_double;
#if HAVE_WORKING_SETENV
  TCase *tc_timeout_env_scale_int;
  TCase *tc_timeout_scale_int;
  TCase *tc_timeout_usr_scale_int;
  TCase *tc_timeout_env_scale_double;
  TCase *tc_timeout_scale_double;
  TCase *tc_timeout_usr_scale_double;
#endif /* HAVE_WORKING_SETENV */
#endif
  TCase *tc_limit;
  TCase *tc_messaging_and_fork;

  s = suite_create("Check Servant");

  tc_simple = tcase_create("Simple Tests");
  tc_signal = tcase_create("Signal Tests");
#if TIMEOUT_TESTS_ENABLED
#if HAVE_WORKING_SETENV
  setenv("CK_DEFAULT_TIMEOUT", "6", 1);
  tc_timeout_env_int = tcase_create("Environment Integer Timeout Tests");
  unsetenv("CK_DEFAULT_TIMEOUT");
  setenv("CK_DEFAULT_TIMEOUT", "0.5", 1);
  tc_timeout_env_double = tcase_create("Environment Double Timeout Tests");
  unsetenv("CK_DEFAULT_TIMEOUT");
#endif /* HAVE_WORKING_SETENV */
  tc_timeout_default = tcase_create("Default Timeout Tests");
  tc_timeout_usr_int = tcase_create("User Integer Timeout Tests");
  tc_timeout_usr_double = tcase_create("User Double Timeout Tests");
#if HAVE_WORKING_SETENV
  setenv("CK_TIMEOUT_MULTIPLIER", "2", 1);
  tc_timeout_scale_int = tcase_create("Timeout Integer Scaling Tests");
  tc_timeout_usr_scale_int = tcase_create("User Integer Timeout Scaling Tests");
  setenv("CK_DEFAULT_TIMEOUT", "6", 1);
  tc_timeout_env_scale_int = tcase_create("Environment Integer Timeout Scaling Tests");
  unsetenv("CK_DEFAULT_TIMEOUT");
  unsetenv("CK_TIMEOUT_MULTIPLIER");
  
  setenv("CK_TIMEOUT_MULTIPLIER", "0.4", 1);
  tc_timeout_scale_double = tcase_create("Timeout Double Scaling Tests");
  tc_timeout_usr_scale_double = tcase_create("User Double Timeout Scaling Tests");
  setenv("CK_DEFAULT_TIMEOUT", "0.9", 1);
  tc_timeout_env_scale_double = tcase_create("Environment Double Timeout Scaling Tests");
  unsetenv("CK_DEFAULT_TIMEOUT");
  unsetenv("CK_TIMEOUT_MULTIPLIER");
#endif /* HAVE_WORKING_SETENV */
#endif /* TIMEOUT_TESTS_ENABLED */
  tc_limit = tcase_create("Limit Tests");
  tc_messaging_and_fork = tcase_create("Msg and fork Tests");

  suite_add_tcase (s, tc_simple);
  suite_add_tcase (s, tc_signal);
#if TIMEOUT_TESTS_ENABLED
#if HAVE_WORKING_SETENV
  suite_add_tcase (s, tc_timeout_env_int);
  suite_add_tcase (s, tc_timeout_env_double);
#endif /* HAVE_WORKING_SETENV */
  suite_add_tcase (s, tc_timeout_default);
  suite_add_tcase (s, tc_timeout_usr_int);
  suite_add_tcase (s, tc_timeout_usr_double);

  /* Add a second time to make sure tcase_set_timeout doesn't contaminate it. */
  suite_add_tcase (s, tc_timeout_default);
#if HAVE_WORKING_SETENV
  suite_add_tcase (s, tc_timeout_env_scale_int);
  suite_add_tcase (s, tc_timeout_env_scale_double);
  suite_add_tcase (s, tc_timeout_scale_int);
  suite_add_tcase (s, tc_timeout_scale_double);
  suite_add_tcase (s, tc_timeout_usr_scale_int);
  suite_add_tcase (s, tc_timeout_usr_scale_double);
#endif
#endif
  suite_add_tcase (s, tc_limit);
  suite_add_tcase (s, tc_messaging_and_fork);

  tcase_add_test (tc_simple, test_lno);
  tcase_add_test (tc_simple, test_mark_lno);
  tcase_add_test (tc_simple, test_pass);
  tcase_add_test (tc_simple, test_fail_unless);
  tcase_add_test (tc_simple, test_fail_if_pass);
  tcase_add_test (tc_simple, test_fail_if_fail);
  tcase_add_test (tc_simple, test_fail_null_msg);
#if defined(__GNUC__)
  tcase_add_test (tc_simple, test_fail_no_msg);
#endif /* __GNUC__ */
  tcase_add_test (tc_simple, test_fail_if_null_msg);
#if defined(__GNUC__)
  tcase_add_test (tc_simple, test_fail_if_no_msg);
#endif /* __GNUC__ */
  tcase_add_test (tc_simple, test_fail_vararg_msg_1);
  tcase_add_test (tc_simple, test_fail_vararg_msg_2);
  tcase_add_test (tc_simple, test_fail_vararg_msg_3);
#if defined(__GNUC__)
  tcase_add_test (tc_simple, test_fail_empty);
#endif /* __GNUC__ */

  tcase_add_test (tc_simple, test_ck_abort);
  tcase_add_test (tc_simple, test_ck_abort_msg);
  tcase_add_test (tc_simple, test_ck_abort_msg_null);
  tcase_add_test (tc_simple, test_ck_assert);
  tcase_add_test (tc_simple, test_ck_assert_null);
  tcase_add_test (tc_simple, test_ck_assert_int_eq);
  tcase_add_test (tc_simple, test_ck_assert_int_ne);
  tcase_add_test (tc_simple, test_ck_assert_int_lt);
  tcase_add_test (tc_simple, test_ck_assert_int_le);
  tcase_add_test (tc_simple, test_ck_assert_int_gt);
  tcase_add_test (tc_simple, test_ck_assert_int_ge);
  tcase_add_test (tc_simple, test_ck_assert_int_expr);
  tcase_add_test (tc_simple, test_ck_assert_uint_eq);
  tcase_add_test (tc_simple, test_ck_assert_uint_ne);
  tcase_add_test (tc_simple, test_ck_assert_uint_lt);
  tcase_add_test (tc_simple, test_ck_assert_uint_le);
  tcase_add_test (tc_simple, test_ck_assert_uint_gt);
  tcase_add_test (tc_simple, test_ck_assert_uint_ge);
  tcase_add_test (tc_simple, test_ck_assert_uint_expr);
  tcase_add_test (tc_simple, test_ck_assert_str_eq);
  tcase_add_test (tc_simple, test_ck_assert_str_ne);
  tcase_add_test (tc_simple, test_ck_assert_str_lt);
  tcase_add_test (tc_simple, test_ck_assert_str_le);
  tcase_add_test (tc_simple, test_ck_assert_str_gt);
  tcase_add_test (tc_simple, test_ck_assert_str_ge);
  tcase_add_test (tc_simple, test_ck_assert_str_expr);
  tcase_add_test (tc_simple, test_ck_assert_ptr_eq);
  tcase_add_test (tc_simple, test_ck_assert_ptr_ne);

  tcase_add_test (tc_signal, test_segv);
  tcase_add_test_raise_signal (tc_signal, test_segv, 11); /* pass  */
  tcase_add_test_raise_signal (tc_signal, test_segv, 8);  /* error */
  tcase_add_test_raise_signal (tc_signal, test_pass, 8);  /* fail  */
  tcase_add_test_raise_signal (tc_signal, test_fail_unless, 8);  /* fail  */
  tcase_add_test (tc_signal, test_fpe);
  tcase_add_test (tc_signal, test_mark_point);

#if TIMEOUT_TESTS_ENABLED
#if HAVE_WORKING_SETENV
  tcase_add_test (tc_timeout_env_int, test_eternal);
  tcase_add_test (tc_timeout_env_int, test_sleep2);
  tcase_add_test (tc_timeout_env_int, test_sleep5);
  tcase_add_test (tc_timeout_env_int, test_sleep9);
  tcase_add_test (tc_timeout_env_double, test_eternal);
#ifdef HAVE_LIBRT
  tcase_add_test (tc_timeout_env_double, test_sleep0_025);
  tcase_add_test (tc_timeout_env_double, test_sleep1);
#endif /* HAVE_LIBRT */
  tcase_add_test (tc_timeout_env_double, test_sleep2);
  tcase_add_test (tc_timeout_env_double, test_sleep5);
  tcase_add_test (tc_timeout_env_double, test_sleep9);
#endif /* HAVE_WORKING_SETENV */

  tcase_add_test (tc_timeout_default, test_eternal);
#ifdef HAVE_LIBRT
  tcase_add_test (tc_timeout_default, test_sleep0_025);
  tcase_add_test (tc_timeout_default, test_sleep1);
#endif /* HAVE_LIBRT */
  tcase_add_test (tc_timeout_default, test_sleep2);
  tcase_add_test (tc_timeout_default, test_sleep5);
  tcase_add_test (tc_timeout_default, test_sleep9);

  tcase_set_timeout (tc_timeout_usr_int, 6);
  tcase_add_test (tc_timeout_usr_int, test_eternal);
  tcase_add_test (tc_timeout_usr_int, test_sleep2);
  tcase_add_test (tc_timeout_usr_int, test_sleep5);
  tcase_add_test (tc_timeout_usr_int, test_sleep9);

  tcase_set_timeout (tc_timeout_usr_double, 0.5);
  tcase_add_test (tc_timeout_usr_double, test_eternal);
#ifdef HAVE_LIBRT
  tcase_add_test (tc_timeout_usr_double, test_sleep0_025);
  tcase_add_test (tc_timeout_usr_double, test_sleep1);
#endif /* HAVE_LIBRT */
  tcase_add_test (tc_timeout_usr_double, test_sleep2);
  tcase_add_test (tc_timeout_usr_double, test_sleep5);
  tcase_add_test (tc_timeout_usr_double, test_sleep9);
  
#if HAVE_WORKING_SETENV
  tcase_add_test (tc_timeout_env_scale_int, test_eternal);
#ifdef HAVE_LIBRT
  tcase_add_test (tc_timeout_env_scale_int, test_sleep0_025);
  tcase_add_test (tc_timeout_env_scale_int, test_sleep1);
#endif /* HAVE_LIBRT */
  tcase_add_test (tc_timeout_env_scale_int, test_sleep2);
  tcase_add_test (tc_timeout_env_scale_int, test_sleep5);
  tcase_add_test (tc_timeout_env_scale_int, test_sleep9);
  tcase_add_test (tc_timeout_env_scale_int, test_sleep14);

  tcase_add_test (tc_timeout_env_scale_double, test_eternal);
#ifdef HAVE_LIBRT
  tcase_add_test (tc_timeout_env_scale_double, test_sleep0_025);
  tcase_add_test (tc_timeout_env_scale_double, test_sleep1);
#endif /* HAVE_LIBRT */
  tcase_add_test (tc_timeout_env_scale_double, test_sleep2);
  tcase_add_test (tc_timeout_env_scale_double, test_sleep5);
  tcase_add_test (tc_timeout_env_scale_double, test_sleep9);
  tcase_add_test (tc_timeout_env_scale_double, test_sleep14);

  tcase_add_test (tc_timeout_scale_int, test_eternal);
#ifdef HAVE_LIBRT
  tcase_add_test (tc_timeout_scale_int, test_sleep0_025);
  tcase_add_test (tc_timeout_scale_int, test_sleep1);
  tcase_add_test (tc_timeout_scale_int, test_sleep2);
#endif /* HAVE_LIBRT */
  tcase_add_test (tc_timeout_scale_int, test_sleep5);
  tcase_add_test (tc_timeout_scale_int, test_sleep9);

  tcase_add_test (tc_timeout_scale_double, test_eternal);
#ifdef HAVE_LIBRT
  tcase_add_test (tc_timeout_scale_double, test_sleep0_025);
  tcase_add_test (tc_timeout_scale_double, test_sleep1);
#endif /* HAVE_LIBRT */
  tcase_add_test (tc_timeout_scale_double, test_sleep2);
  tcase_add_test (tc_timeout_scale_double, test_sleep5);
  tcase_add_test (tc_timeout_scale_double, test_sleep9);
  
  setenv("CK_TIMEOUT_MULTIPLIER", "2", 1);
  tcase_set_timeout (tc_timeout_usr_scale_int, 6);
  unsetenv("CK_TIMEOUT_MULTIPLIER");
  tcase_add_test (tc_timeout_usr_scale_int, test_eternal);
#ifdef HAVE_LIBRT
  tcase_add_test (tc_timeout_usr_scale_int, test_sleep0_025);
  tcase_add_test (tc_timeout_usr_scale_int, test_sleep1);
#endif /* HAVE_LIBRT */
  tcase_add_test (tc_timeout_usr_scale_int, test_sleep2);
  tcase_add_test (tc_timeout_usr_scale_int, test_sleep5);
  tcase_add_test (tc_timeout_usr_scale_int, test_sleep9);
  tcase_add_test (tc_timeout_usr_scale_int, test_sleep14);
  
  setenv("CK_TIMEOUT_MULTIPLIER", "0.4", 1);
  tcase_set_timeout (tc_timeout_usr_scale_double, 0.9);
  unsetenv("CK_TIMEOUT_MULTIPLIER");
  tcase_add_test (tc_timeout_usr_scale_double, test_eternal);
#ifdef HAVE_LIBRT
  tcase_add_test (tc_timeout_usr_scale_double, test_sleep0_025);
  tcase_add_test (tc_timeout_usr_scale_double, test_sleep1);
#endif /* HAVE_LIBRT */
  tcase_add_test (tc_timeout_usr_scale_double, test_sleep2);
  tcase_add_test (tc_timeout_usr_scale_double, test_sleep5);
  tcase_add_test (tc_timeout_usr_scale_double, test_sleep9);
  tcase_add_test (tc_timeout_usr_scale_double, test_sleep14);
#endif
#endif

  tcase_add_test (tc_limit, test_early_exit);
  tcase_add_test (tc_limit, test_null);
  tcase_add_test (tc_limit, test_null_2);

#ifdef _POSIX_VERSION
  tcase_add_test (tc_messaging_and_fork, test_fork1p_pass);
  tcase_add_test (tc_messaging_and_fork, test_fork1p_fail);
  tcase_add_test (tc_messaging_and_fork, test_fork1c_pass);
  tcase_add_test (tc_messaging_and_fork, test_fork1c_fail);
  tcase_add_test (tc_messaging_and_fork, test_fork2_pass);
  tcase_add_test (tc_messaging_and_fork, test_fork2_fail);
#endif /* _POSIX_VERSION */

  return s;
}
