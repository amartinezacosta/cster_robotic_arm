#ifndef PID_H
#define PID_H

#define MAX_INTEGRAL_VALUE     26666.0f
#define MIN_INTEGRAL_VALUE    -26666.0f

typedef struct
{
  float kp,ki,kd;
  float max_output, min_output;
  float prev_input;
  float set_point;
  float integral;
}pid_t;

float pid_init(pid_t * const me,
               float kp,
               float ki,
               float kd,
               float max_output,
               float min_output
               );
float pid_update(pid_t * const me, float input, float dt);
float pid_set_point(pid_t * const me, float set_point);

#endif
