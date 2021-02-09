
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

// Automatically generated file
#include <array>

#include <e_float/e_float_complex.h>
#include <e_float/e_float_functions.h>
#include <e_float/e_float_functions_complex.h>

#include "../test_case_imag.h"

namespace test
{
  namespace imag
  {
    class TestCase_case_02114_z_various_trig : public TestCaseImag
    {
    public:
      TestCase_case_02114_z_various_trig() { }
      virtual ~TestCase_case_02114_z_various_trig() { }
    private:
      virtual const std::string& name() const
      {
        static const std::string str("TestCase_case_02114_z_various_trig");
        return str;
      }
      virtual void e_float_test(std::vector<ef::complex<e_float>>& data) const
      {
        data.clear();
        data.push_back(              ef::tan(ef::complex<e_float>(ef::euler_gamma() * ef::three(), ef::phi() * ef::seven())));
        data.push_back(e_float(1U) / ef::tan(ef::complex<e_float>(ef::euler_gamma() * ef::three(), ef::phi() * ef::seven())));
        data.push_back(e_float(1U) / ef::cos(ef::complex<e_float>(ef::euler_gamma() * ef::three(), ef::phi() * ef::seven())));
        data.push_back(e_float(1U) / ef::sin(ef::complex<e_float>(ef::euler_gamma() * ef::three(), ef::phi() * ef::seven())));
      }
      virtual const std::vector<ef::complex<e_float>>& control_data() const
      {
        static const std::array<ef::complex<e_float>, 4U> a =
        {{
           ef::complex<e_float>(e_float("-9.185876550411305625315065383130942823496349736917366134565031365023601190537557633847406227310047814481718702053803978509883244453911230007460541903301551482690775553782016451457135795301215963376371740888355192301907547106413475392741266454524732197142665753042582811511990779212872208946837627912549921643840477446034442787146374925481412752151470907463294259421297413116452613057379177113e-11"), e_float("1.00000000027562151472435723132782281500837417348264371689635254533561214211034004895895861932422090603200434253295398435512894799484286357438870550418361583233326789268618979697864660663884849918102106318036135334099537673900563690673580911980446910890004491701857215423888029315155664650967656499183543185492518666340679882625774435573489582113845652642342846437990869909433270368776216281217413104681")),
           ef::complex<e_float>(e_float("-9.185876545347655209540396183015285821493842418070555944672684439807784192438428685463511994184160090639075829558901240327902037189703849079244476579680529716650462649712451572877223167277759707075828942333247179946119461546704950002673972340294098081066282322825922532492673614959382526419205103461372521570588515016709040764784637979962640862815514833713257852536208511973498274932746553882e-11"), e_float("-0.99999999972437848534317195523722553434966702699395588238784901091133173661212885730735365822122101053760421298448287597189087710688219136365191806441232831043857979939416140095371245184674832407153338292659173340926198985253427271300609237566587624511112494092053601385817714463685337347237982817713416648428649922929495882908458001281141753147304760586715213351588232698062823136522490387483303898718")),
           ef::complex<e_float>(e_float("-3.860609464918929059065958981680562238169572869613842484022392390285219045388263671809220168918056497593533180508037309543172647958667986599367561336971866802909410838236399888493630220208631911946597122917726750271603463486501490503357511876284563994162648576448371331114009462213211790116039591073506548957389053574323085429619811592058206810950865625936881980492810566039329762325667314031117485273e-6"), e_float("0.000023793850780335352623736517167183601070874401143261780058913702367185966954149353130845520222821205400287495873619595315544666257061600092228091870911591802474626108713875286389218183223891132196547402812707244547971453188440863041332921554680503792970400130642377554275748927824576407211738366652361130560920565197698873327791184199079563028668628954404408661714327765505596701931396699167737442008485")),
           ef::complex<e_float>(e_float("0.000023793850774131886251487396881507314122403006371603903619316071994879173895106297557989945303488110660425513466078942860524820387196502490871915504377494871425788730562765694404827849270582061744460127214852619792054371632176061228269569484273060131647994872793438105606586694008054284656723522077163167497287204879908432306779977608007693802098498422707138551648113009665532457706284469885094851442841"), e_float("3.860609461669188272780672109931887188113229657941080861925709800047187009719058483631123113433705743600909002160401830798056862427677087815890736344146790608378076079570255248579352136314376649934672454572622699850141575286487596340309442543752683437273999944052434739379746874557533862464213353431658384305820011976609336619821499708470446150249796430068298291938509980974984081423712906642187801229e-6")),
        }};
        static const std::vector<ef::complex<e_float>> v(a.cbegin(), a.cend());
        return v;
      }
    };

    bool test_case_02114_z_various_trig(const bool b_write_output)
    {
      return TestCase_case_02114_z_various_trig().execute(b_write_output);
    }
  }
}
