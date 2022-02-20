/** addition operator */
VSControl operator+ (const VSControl& v2) const;

/** gain multiplication */
VSControl operator* (const float& g) const;

/** Corresponding widget name */
static const char* getWidgetName(unsigned idx);

/** Get number of members */
static const unsigned size();

/** Access members by index */
template<typename idx_t>
inline float& operator[] (idx_t idx)
{ return accessValue(idx); }

/** Access members by index, read-only */
template<typename idx_t>
inline const float operator[] (idx_t idx) const
{ return getValue(idx); }

/** Set value by index */
float getValue(unsigned idx) const;

/** Access by index */
float& accessValue(unsigned idx);

/** Construct from array */
VSControl(const std::vector<float>& m);

/** maximum val */
static const unsigned idx_max = 9U;
