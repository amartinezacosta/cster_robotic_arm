#include <pid.h>

float pid_init(pid_t * const me,
               float kp,
               float ki,
               float kd,
               float max_output,
               float min_output
               )
{
  me->kp = kp;
  me->ki = ki;
  me->kd = kd;
  me->integral = 0;
  me->prev_input = 0;
  me->max_output = max_output;
  me->min_output = min_output;
}

float pid_update(pid_t * const me, float input, float dt)
{
  float error = me->set_point - input;

  /*Calculate proportional value*/
  float proportional = me->kp * error;

  /*Calculate and clamp integral value*/
  me->integral += me->ki*(error*dt);
  me->integral = (me->integral > MAX_INTEGRAL_VALUE) ?
                  MAX_INTEGRAL_VALUE : me->integral;
  me->integral = (me->integral < MIN_INTEGRAL_VALUE) ?
                  MIN_INTEGRAL_VALUE : me->integral;

  float derivative = me->kd*((input - me->prev_input)/dt);
  me->prev_input = input;

  /*Compute output and clamp it*/
  float output = proportional + me->integral + derivative;

  output = (output > me->max_output) ?
            me->max_output : output;
  output = (output < me->min_output) ?
            me->min_output : output;

  return output;
}

float pid_set_point(pid_t * const me, float set_point)
{
  me->set_point = set_point;
}
