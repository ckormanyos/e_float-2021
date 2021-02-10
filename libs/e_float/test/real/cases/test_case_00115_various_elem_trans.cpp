
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

// Automatically generated file
#include <array>

#include <e_float/e_float_functions.h>

#include <../test/real/test_case_real.h>

namespace test
{
  namespace real
  {
    class TestCase_case_00115_various_elem_trans : public TestCaseReal
    {
    public:
      TestCase_case_00115_various_elem_trans() { }
      virtual ~TestCase_case_00115_various_elem_trans() { }
    private:
      virtual const std::string& name() const
      {
        static const std::string str("TestCase_case_00115_various_elem_trans");
        return str;
      }
      virtual void e_float_test(std::vector<e_float>& data) const
      {
        data.clear();
        data.push_back(ef::sqrt(e_float(11.1))); // 11.1 = ((1745144855606067 / (2^52)) + 1)*2^3
        data.push_back(ef::sqrt(e_float(22.2))); // 22.2 = ((1745144855606067 / (2^52)) + 1)*2^4
        data.push_back(ef::log1p(static_cast<std::int32_t>(-1) / ef::hundred()));
        data.push_back(ef::log1p(static_cast<std::int32_t>(+1) / ef::hundred()));
        data.push_back(ef::log10(ef::googol() * ef::phi()));
        data.push_back(ef::loga (ef::pi(), ef::googol() * ef::phi()));
        data.push_back(ef::log  (e_float("1e123456")));
        data.push_back(ef::rootn(ef::euler_gamma(), static_cast<std::int32_t>(-7)));
      }
      virtual const std::vector<e_float>& control_data() const
      {
        static const std::array<e_float, 8U> a =
        {{
           e_float("3.3316662497915363138017163351050740123029099404822263642011324887361626333558150778943533677637033852673761075733661241535342719324629412883795681516684595884259268627913404262698569001388965568579231675187485558329325678097009983335981666643323669647023172913052529896427425627605165069270478920195155121935680494401807193457394645472702812758807294047102066177904446251427303897345426471649668398615"),
           e_float("4.7116875957558985098507875162620128061690129475788801227532106780480120234163983259079985174011014332776991522160890636247110110769880225928638579539128076654921277662524537327000443832648428441830990733809094397245318223471375065264940204243134836041847961189594406872096267287163107081796284624043272768827675656320697454316172675363077975284048373464815879028949851595944321610035771701332253153366"),
           e_float("-0.010050335853501441183548857558547706085515007674629873378699425529583009004250313649708192549097627693279784064518767259827473319708786475871668605861900492707846971603671530739391724025806230580247206178651645427569342330598199181125422436874243602929435950123041048547079391723158859144438310470116120194111146550799330396389404157201875299396788203912427422325468369532304795524249400872590112915071"),
           e_float("0.0099503308531680828482153575442607416886796099400587978646095597668666642476389110326856965627601611645256051738464847880707475234877013112485359899665628564615468674191312254128121384929569634035662311420062749767020318080945113711680039487500861722298334709833134706415660301243104390365074857226746826501028437726918533176144446994112862867598814525626236527610233794421932638497942402215935006079414"),
           e_float("100.20898764024997873376927208923755541682245923991821095353928756139741048534967459632776585562351035351450168279393653384377181221588575053767857396519531022492161571821650076544044755702710430160168973617276515179677189567495062550107492963593473020068408166880914011743653172998209568582678896715345583697967065712022525624992802949423231363066249572791180750909152692390646879724754099213207878112"),
           e_float("201.56695826391669891484060229457840074352824649555937585851861180389637401059597587799569259785560793163073675211472303135610446118016780242304069326235745807669960224796458389314767508512512810379927640063544680457647936488714348314346217461244266504034907313854230812616314236986801579828197719483431548799748324821557239155549153865686727284736763212173136334893737530035299042023762017056115427251"),
           e_float("284267.94524067290396612515302951286761360158538015379652917052934185264410032722780001527095154144752010597474672449111128620637581726299095099317343945919225680179231103967867825215981566744575752134859142362967335942683194454033875007143433818129501172005025768002458172123478515751450789318963382020743722516415433160998653579931174513065026878220544933245636804124882807355274273332096842746857206"),
           e_float("1.0816694299524247579186153119085360789866650367992017603390843068161712998339498702396791674218642297226347712334248832546074085808835706417784928170735620244190695455851396464915714066595194789754021280462136599159520731442914812014989757230840645193891962711843707194438177711168288706642437636252590584704473197327587784575627509258978908094415555821145639234371041850584058577985441019352338096049"),
        }};
        static const std::vector<e_float> v(a.cbegin(), a.cend());
        return v;
      }
    };

    bool test_case_00115_various_elem_trans(const bool b_write_output)
    {
      return TestCase_case_00115_various_elem_trans().execute(b_write_output);
    }
  }
}
