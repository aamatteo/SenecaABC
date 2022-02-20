
#if GENCODEGEN < 110
APInfoLogBlock::APInfoLogBlock(const int axis, const unsigned size) :
  axis(axis),
  Iservo_variable_size(size),
  Iservo(new float[size]),
  delta_drum_variable_size(size),
  delta_drum(new float[size]),
  delta_t_variable_size(size),
  delta_t(new float[size]),
  delta_variable_size(size),
  delta(new float[size])
{
  //
}
#else
APInfoLogBlock::APInfoLogBlock(const int axis, const unsigned size) :
  axis(axis),
  Iservo(size),
  delta_drum(size),
  delta_t(size),
  delta(size)
{
  //
}
#endif
