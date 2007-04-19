#include <algorithm>

// Delete pointers in an STL sequence container.
template<class Seq> void Purge(Seq &container)
{
  typename Seq::iterator it;
  for(it = container.begin(); it != container.end(); ++it)
    delete *it;
  container.clear();
}
