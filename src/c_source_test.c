/*
 * DO NOT EDIT THIS FILE. Generated by checkmk.
 * Edit the original source file "test.check" instead.
 */

#include <check.h>

#include "Viewer/afina.h"
#include "Viewer/giga.h"

#define PATH "./cube.txt"

START_TEST(count_vertexes_and_edges0) {
  unsigned vertexes = 0;
  unsigned edges = 0;
  min_max_t start = {0, 0, 0, 0};
  count_vertexes_and_edges(PATH, &vertexes, &edges, &start);
  ck_assert_int_eq(vertexes, 8);
  ck_assert_int_eq(edges, 72);
}
END_TEST

START_TEST(get_vertexes_and_edgest_data0) {
  unsigned vertexes = 0;
  unsigned edges = 0;
  min_max_t start = {0, 0, 0, 0};
  count_vertexes_and_edges(PATH, &vertexes, &edges, &start);
  double *vertexes_data = NULL;
  unsigned *edges_data = NULL;
  get_vertexes_and_edges_data(PATH, vertexes, edges, &vertexes_data,
                              &edges_data);

  const unsigned original_v = 8;
  const unsigned original_e = 72;
  const double original_ver_data[] = {1.000000,  -1.000000, -1.000000,
                                      1.000000,  -1.000000, 1.000000,
                                      -1.000000, -1.000000};
  const unsigned original_edge_data[] = {
      1, 2, 2, 3, 3, 1, 7, 6, 6, 5, 5, 7, 4, 5, 5, 1, 1, 4, 5, 6, 6, 2, 2, 5,
      2, 6, 6, 7, 7, 2, 0, 3, 3, 7, 7, 0, 0, 1, 1, 3, 3, 0, 4, 7, 7, 5, 5, 4,
      0, 4, 4, 1, 1, 0, 1, 5, 5, 2, 2, 1, 3, 2, 2, 7, 7, 3, 4, 0, 0, 7, 7, 4};
  for (size_t i = 0; i < original_v; i++) {
    ck_assert_double_eq_tol(original_ver_data[i], vertexes_data[i], 1e-6);
  }
  for (size_t j = 0; j < original_e; j++) {
    ck_assert_int_eq(original_edge_data[j], edges_data[j]);
  }
  free(vertexes_data);
  free(edges_data);
}
END_TEST

START_TEST(afina_move0) {
  Axis_t move_to;
  move_to.x = 1.15;
  move_to.y = 0.7;
  move_to.z = -1.2;
  double *vertexes_data = NULL;
  unsigned *edges_data = NULL;
  const double original_ver_data[] = {2.150000, -0.300000, -2.200000,
                                      2.150000, -0.300000, -0.200000,
                                      0.150000, -0.300000};
  get_vertexes_and_edges_data(PATH, 8, 72, &vertexes_data, &edges_data);
  afina_move(vertexes_data, 24, move_to);
  for (size_t i = 0; i < 8; i++) {
    ck_assert_double_eq_tol(original_ver_data[i], vertexes_data[i], 1e-6);
  }
  free(vertexes_data);
  free(edges_data);
}
END_TEST

START_TEST(afina_rotate_x0) {
  double angle = 1;
  double *vertexes_data = NULL;
  unsigned *edges_data = NULL;
  const double original_ver_data[] = {1.000000,  0.301169,  -1.381773,
                                      1.000000,  -1.381773, -0.301169,
                                      -1.000000, -1.381773};
  get_vertexes_and_edges_data(PATH, 8, 72, &vertexes_data, &edges_data);
  afina_rotate_x(vertexes_data, 24, angle);
  for (size_t i = 0; i < 8; i++) {
    ck_assert_double_eq_tol(original_ver_data[i], vertexes_data[i], 1e-6);
  }
  free(vertexes_data);
  free(edges_data);
}
END_TEST

START_TEST(afina_rotate_y0) {
  double angle = 1;
  double *vertexes_data = NULL;
  unsigned *edges_data = NULL;
  const double original_ver_data[] = {-0.301169, -1.000000, -1.381773,
                                      1.381773,  -1.000000, -0.301169,
                                      0.301169,  -1.000000};
  get_vertexes_and_edges_data(PATH, 8, 72, &vertexes_data, &edges_data);
  afina_rotate_y(vertexes_data, 24, angle);
  for (size_t i = 0; i < 8; i++) {
    ck_assert_double_eq_tol(original_ver_data[i], vertexes_data[i], 1e-6);
  }
  free(vertexes_data);
  free(edges_data);
}
END_TEST

START_TEST(afina_rotate_z0) {
  double angle = 1;
  double *vertexes_data = NULL;
  unsigned *edges_data = NULL;
  const double original_ver_data[] = {1.381773, 0.301169, -1.000000, 1.381773,
                                      0.301169, 1.000000, 0.301169,  -1.381773};
  get_vertexes_and_edges_data(PATH, 8, 72, &vertexes_data, &edges_data);
  afina_rotate_z(vertexes_data, 24, angle);
  for (size_t i = 0; i < 8; i++) {
    ck_assert_double_eq_tol(original_ver_data[i], vertexes_data[i], 1e-6);
  }
  free(vertexes_data);
  free(edges_data);
}
END_TEST

START_TEST(afina_scale0) {
  double scale = 13.8;
  double *vertexes_data = NULL;
  unsigned *edges_data = NULL;
  const double original_ver_data[] = {13.800000,  -13.800000, -13.800000,
                                      13.800000,  -13.800000, 13.800000,
                                      -13.800000, -13.800000};
  get_vertexes_and_edges_data(PATH, 8, 72, &vertexes_data, &edges_data);
  afina_scale(vertexes_data, 24, scale);
  for (size_t i = 0; i < 8; i++) {
    ck_assert_double_eq_tol(original_ver_data[i], vertexes_data[i], 1e-6);
  }
  free(vertexes_data);
  free(edges_data);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, count_vertexes_and_edges0);
  tcase_add_test(tc1_1, get_vertexes_and_edgest_data0);
  tcase_add_test(tc1_1, afina_move0);
  tcase_add_test(tc1_1, afina_rotate_x0);
  tcase_add_test(tc1_1, afina_rotate_y0);
  tcase_add_test(tc1_1, afina_rotate_z0);
  tcase_add_test(tc1_1, afina_scale0);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
