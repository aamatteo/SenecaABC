VSControl VSControl::operator+ (const VSControl& v2) const
{
  return VSControl(this->Delta_Cmq + v2.Delta_Cmq,
		   this->Delta_Cmu + v2.Delta_Cmu,
		   this->Delta_Cmalpha + v2.Delta_Cmalpha,
		   this->K_de_Sy + v2.K_de_Sy,
		   this->Delta_Clp + v2.Delta_Clp,
		   this->Delta_Clr + v2.Delta_Clr,
		   this->Delta_Clbeta + v2.Delta_Clbeta,
		   this->K_da_Sx + v2.K_da_Sx,
                   this->de_trim + v2.de_trim);
}

VSControl VSControl::operator* (const float& g) const
{
  return VSControl(g * this->Delta_Cmq,
		   g * this->Delta_Cmu,
		   g * this->Delta_Cmalpha,
		   g * this->K_de_Sy,
		   g * this->Delta_Clp,
		   g * this->Delta_Clr,
		   g * this->Delta_Clbeta,
		   g * this->K_da_Sx,
                   g * this->de_trim);
}

static const char* vstab_widgets[] = {
  "vstab_cmq", "vstab_cmu", "vstab_cmalpha", "vstab_ky",
  "vstab_clp", "vstab_clr", "vstab_clbeta",  "vstab_kx", "vstab_de_trim" };

const char* VSControl::getWidgetName(unsigned idx)
{
  if (idx < idx_max) {
    return vstab_widgets[idx];
  }
  return "";
}

const unsigned VSControl::size()
{
  return idx_max;
}

float VSControl::getValue(unsigned idx) const
{
  switch(idx) {
  case 0: return this->Delta_Cmq;
  case 1: return this->Delta_Cmu;
  case 2: return this->Delta_Cmalpha;
  case 3: return this->K_de_Sy;
  case 4: return this->Delta_Clp;
  case 5: return this->Delta_Clr;
  case 6: return this->Delta_Clbeta;
  case 7: return this->K_da_Sx;
  case 8: return this->de_trim;
  default:
    cerr << "no index VS parameters " << idx;
    return 0.0;
  }
}

float& VSControl::accessValue(unsigned idx)
{
  static float noval = 0.0f;
  switch(idx) {
  case 0: return this->Delta_Cmq;
  case 1: return this->Delta_Cmu;
  case 2: return this->Delta_Cmalpha;
  case 3: return this->K_de_Sy;
  case 4: return this->Delta_Clp;
  case 5: return this->Delta_Clr;
  case 6: return this->Delta_Clbeta;
  case 7: return this->K_da_Sx;
  case 8: return this->de_trim;
  default:
    cerr << "no index VS parameters " << idx;
    return noval;
  }
}

VSControl::VSControl(const std::vector<float>& m) :
  Delta_Cmq(m.size() > 0 ? m[0] : 0.0),
  Delta_Cmu(m.size() > 1 ? m[1] : 0.0),
  Delta_Cmalpha(m.size() > 2 ? m[2] : 0.0),
  K_de_Sy(m.size() > 3 ? m[3] : 0.0),
  Delta_Clp(m.size() > 4 ? m[4] : 0.0),
  Delta_Clr(m.size() > 5 ? m[5] : 0.0),
  Delta_Clbeta(m.size() > 6 ? m[6] : 0.0),
  K_da_Sx(m.size() > 7 ? m[7] : 0.0),
  de_trim(m.size() > 8 ? m[8] : 0.0)
{
  //
}
