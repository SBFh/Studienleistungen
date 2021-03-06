double calcNewton(double (*function)(double), double start, double end, unsigned int segments, unsigned int degree, unsigned int divisor, const double coeff[])
{
  double seg_step = (end - start)/segments;
  double f_val = 0;

  for(unsigned int s = 0; s < segments; ++s){

      double seg_a = start + seg_step*s;
      double seg_b = seg_a + seg_step;
      double f_subval = 0;

      for(unsigned int i = 0; i < degree + 1; ++i){
	  f_subval += coeff[i] * function(seg_a + i*(seg_b - seg_a)/degree);
      }

      f_val += ((seg_b - seg_a)/divisor) * f_subval;
  }
  
  return f_val;
}