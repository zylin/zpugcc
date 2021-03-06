// 2004-02-09  Petur Runolfsson  <peturr02@ru.is>

// Copyright (C) 2004 Free Software Foundation
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 2, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING.  If not, write to the Free
// Software Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307,
// USA.

// 22.1.1.5 locale static members [lib.locale.statics]

#include <locale>
#include <clocale>
#include <testsuite_hooks.h>

// libstdc++/14071
void test01()
{
  using namespace std;
  bool test __attribute__((unused)) = true;

  const locale loc_is = __gnu_test::try_named_locale("is_IS");
  const locale loc_en = __gnu_test::try_named_locale("en_US");

  const locale loc(loc_is, loc_en, locale::monetary);

  if (loc.name() != "*")
    {
      locale::global(loc);
      VERIFY( loc.name() == setlocale(LC_ALL, NULL) );
    }
}

int main()
{
  test01();
  return 0;
}
