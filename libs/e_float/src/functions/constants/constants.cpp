
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#if defined(_MSC_VER)
  #pragma warning (disable:4127)
#endif

#include <e_float/e_float_functions.h>

const e_float& ef::two                   () { static const e_float val(         2U); return val; }
const e_float& ef::three                 () { static const e_float val(         3U); return val; }
const e_float& ef::four                  () { static const e_float val(         4U); return val; }
const e_float& ef::five                  () { static const e_float val(         5U); return val; }
const e_float& ef::six                   () { static const e_float val(         6U); return val; }
const e_float& ef::seven                 () { static const e_float val(         7U); return val; }
const e_float& ef::eight                 () { static const e_float val(         8U); return val; }
const e_float& ef::nine                  () { static const e_float val(         9U); return val; }
const e_float& ef::ten                   () { static const e_float val(        10U); return val; }
const e_float& ef::fifty                 () { static const e_float val(        50U); return val; }
const e_float& ef::hundred               () { static const e_float val(       100U); return val; }
const e_float& ef::thousand              () { static const e_float val(      1000U); return val; }
const e_float& ef::million               () { static const e_float val(   1000000U); return val; }
const e_float& ef::billion               () { static const e_float val(1000000000U); return val; }
const e_float& ef::trillion              () { static const e_float val(     "1e12"); return val; }
const e_float& ef::googol                () { static const e_float val(    "1e100"); return val; }

const e_float& ef::int32_min             () { static const e_float val((std::numeric_limits<std::int32_t>::min)());       return val; }
const e_float& ef::int32_max             () { static const e_float val((std::numeric_limits<std::int32_t>::max)());       return val; }
const e_float& ef::int64_min             () { static const e_float val((std::numeric_limits<std::int64_t>::min)());       return val; }
const e_float& ef::int64_max             () { static const e_float val((std::numeric_limits<std::int64_t>::max)());       return val; }
const e_float& ef::unsigned_long_long_max() { static const e_float val((std::numeric_limits<unsigned long long>::max)()); return val; }
const e_float& ef::signed_long_long_min  () { static const e_float val((std::numeric_limits<signed long long>::min)());   return val; }
const e_float& ef::signed_long_long_max  () { static const e_float val((std::numeric_limits<signed long long>::max)());   return val; }
const e_float& ef::double_min            () { static const e_float val((std::numeric_limits<double>::min)());             return val; }
const e_float& ef::double_max            () { static const e_float val((std::numeric_limits<double>::max)());             return val; }
const e_float& ef::long_double_min       () { static const e_float val((std::numeric_limits<long double>::min)());        return val; }
const e_float& ef::long_double_max       () { static const e_float val((std::numeric_limits<long double>::max)());        return val; }

const e_float& ef::one_minus             () { static const e_float val(-1 ); return val; }

const e_float& ef::tenth                 () { static const e_float val(ef::one()  / static_cast<std::int32_t>(10)); return val; }
const e_float& ef::eighth                () { static const e_float val(ef::one()  / static_cast<std::int32_t>( 8)); return val; }
const e_float& ef::fifth                 () { static const e_float val(ef::one()  / static_cast<std::int32_t>( 5)); return val; }
const e_float& ef::quarter               () { static const e_float val(ef::one()  / static_cast<std::int32_t>( 4)); return val; }
const e_float& ef::third                 () { static const e_float val(ef::one()  / static_cast<std::int32_t>( 3)); return val; }
const e_float& ef::two_third             () { static const e_float val(ef::two()  / static_cast<std::int32_t>( 3)); return val; }
const e_float& ef::three_half            () { static const e_float val(ef::one() + ef::half());                     return val; }

const e_float& ef::sqrt2()
{
  // 1100 digits of sqrt(2)
  static const std::string str =
    std::string("1.")
  + std::string("4142135623730950488016887242096980785696718753769480731766797379907324784621070388503875343276415727")
  + std::string("3501384623091229702492483605585073721264412149709993583141322266592750559275579995050115278206057147")
  + std::string("0109559971605970274534596862014728517418640889198609552329230484308714321450839762603627995251407989")
  + std::string("6872533965463318088296406206152583523950547457502877599617298355752203375318570113543746034084988471")
  + std::string("6038689997069900481503054402779031645424782306849293691862158057846311159666871301301561856898723723")
  + std::string("5288509264861249497715421833420428568606014682472077143585487415565706967765372022648544701585880162")
  + std::string("0758474922657226002085584466521458398893944370926591800311388246468157082630100594858704003186480342")
  + std::string("1948972782906410450726368813137398552561173220402450912277002269411275736272804957381089675040183698")
  + std::string("6836845072579936472906076299694138047565482372899718032680247442062926912485905218100445984215059112")
  + std::string("0249441341728531478105803603371077309182869314710171111683916581726889419758716582152128229518488472")
  + std::string("0896946338628915628827659526351405422676532396946175112916024087155101351504553812875600526314680171")
  ;

  static const e_float val(str.c_str());
  return val;
}

const e_float& ef::pi()
{
  if(std::numeric_limits<e_float>::digits10 < 1010)
  {
    // 1100 digits of pi
    static const std::string str =
      std::string("3.")
    + std::string("1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679")
    + std::string("8214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196")
    + std::string("4428810975665933446128475648233786783165271201909145648566923460348610454326648213393607260249141273")
    + std::string("7245870066063155881748815209209628292540917153643678925903600113305305488204665213841469519415116094")
    + std::string("3305727036575959195309218611738193261179310511854807446237996274956735188575272489122793818301194912")
    + std::string("9833673362440656643086021394946395224737190702179860943702770539217176293176752384674818467669405132")
    + std::string("0005681271452635608277857713427577896091736371787214684409012249534301465495853710507922796892589235")
    + std::string("4201995611212902196086403441815981362977477130996051870721134999999837297804995105973173281609631859")
    + std::string("5024459455346908302642522308253344685035261931188171010003137838752886587533208381420617177669147303")
    + std::string("5982534904287554687311595628638823537875937519577818577805321712268066130019278766111959092164201989")
    + std::string("3809525720106548586327886593615338182796823030195203530185296899577362259941389124972177528347913152")
    ;

    static const e_float val(str.c_str());
    return val;
  }
  else
  {
    static bool is_initialized = false;
    static e_float val_pi;

    if(!is_initialized)
    {
      is_initialized = true;

      e_float a(1U);
      e_float bB("0.5");
      e_float s (bB);
      e_float t ("0.375");

      // This loop is designed for a maximum of several million
      // decimal digits of pi. The index k should reach no higher
      // than about 25. The decimal precision after 18 iterations
      // is more than one million digits.

      for(std::int32_t k = static_cast<std::int32_t>(1); k < static_cast<std::int32_t>(64); k++)
      {
        bB      = ef::sqrt(bB);
        a      += bB;
        a      /= static_cast<std::int32_t>(2);
        val_pi  = a;
        val_pi *= a;
        bB      = val_pi;
        bB     -= t;
        bB     *= static_cast<std::int32_t>(2);

        e_float iterate_term(bB);
        iterate_term -= val_pi;
        iterate_term *= static_cast<std::int32_t>(1UL << k);
        s += iterate_term;

        const std::int32_t d10 = static_cast<std::int32_t>(-iterate_term.order());

        // Test the significant digits of the last iteration change.
        // If it is large enough, then the calculation is finished.
        if(d10 >= static_cast<std::int32_t>((ef::tolerance() / 2) + 10))
        {
          break;
        }

        t   = val_pi;
        t  += bB;
        t  /= static_cast<std::int32_t>(4);
      }

      val_pi += bB;
      val_pi *= s.calculate_inv();
    }

    static const e_float val(val_pi);
    return val;
  }
}

const e_float& ef::pi_half   () { static const e_float val = ef::pi() / static_cast<std::int32_t>(2);   return val; }
const e_float& ef::pi_squared() { static const e_float val = ef::pi() * ef::pi();                       return val; }
const e_float& ef::two_pi    () { static const e_float val = ef::pi() * static_cast<std::int32_t>(2);   return val; }
const e_float& ef::sqrt_pi   () { static const e_float val = ef::sqrt(ef::pi());                        return val; }

const e_float& ef::e()
{
  // 1100 digits of e
  static const std::string str =
    std::string("2.")
  + std::string("7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274")
  + std::string("2746639193200305992181741359662904357290033429526059563073813232862794349076323382988075319525101901")
  + std::string("1573834187930702154089149934884167509244761460668082264800168477411853742345442437107539077744992069")
  + std::string("5517027618386062613313845830007520449338265602976067371132007093287091274437470472306969772093101416")
  + std::string("9283681902551510865746377211125238978442505695369677078544996996794686445490598793163688923009879312")
  + std::string("7736178215424999229576351482208269895193668033182528869398496465105820939239829488793320362509443117")
  + std::string("3012381970684161403970198376793206832823764648042953118023287825098194558153017567173613320698112509")
  + std::string("9618188159304169035159888851934580727386673858942287922849989208680582574927961048419844436346324496")
  + std::string("8487560233624827041978623209002160990235304369941849146314093431738143640546253152096183690888707016")
  + std::string("7683964243781405927145635490613031072085103837505101157477041718986106873969655212671546889570350354")
  + std::string("0212340784981933432106817012100562788023519303322474501585390473041995777709350366041699732972508869")
  ;

  static const e_float val(str.c_str());
  return val;
}

const e_float& ef::ln2()
{
  // TBD: Gauss AGM for high digit counts.

  // 1100 digits of ln2
  static const std::string str =
    std::string("0.")
  + std::string("6931471805599453094172321214581765680755001343602552541206800094933936219696947156058633269964186875")
  + std::string("4200148102057068573368552023575813055703267075163507596193072757082837143519030703862389167347112335")
  + std::string("0115364497955239120475172681574932065155524734139525882950453007095326366642654104239157814952043740")
  + std::string("4303855008019441706416715186447128399681717845469570262716310645461502572074024816377733896385506952")
  + std::string("6066834113727387372292895649354702576265209885969320196505855476470330679365443254763274495125040606")
  + std::string("9438147104689946506220167720424524529612687946546193165174681392672504103802546259656869144192871608")
  + std::string("2938031727143677826548775664850856740776484514644399404614226031930967354025744460703080960850474866")
  + std::string("3852313818167675143866747664789088143714198549423151997354880375165861275352916610007105355824987941")
  + std::string("4729509293113897155998205654392871700072180857610252368892132449713893203784393530887748259701715591")
  + std::string("0708823683627589842589185353024363421436706118923678919237231467232172053401649256872747782344535347")
  + std::string("6481149418642386776774406069562657379600867076257199184734022651462837904883062033061144630073719489")
  ;

  static const e_float val(str.c_str());
  return val;
}

const e_float& ef::ln10()
{
  // TBD: Gauss AGM for high digit counts.

  // 1100 digits of ln10
  static const std::string str =
    std::string("2.")
  + std::string("3025850929940456840179914546843642076011014886287729760333279009675726096773524802359972050895982983")
  + std::string("4196778404228624863340952546508280675666628736909878168948290720832555468084379989482623319852839350")
  + std::string("5308965377732628846163366222287698219886746543667474404243274365155048934314939391479619404400222105")
  + std::string("1017141748003688084012647080685567743216228355220114804663715659121373450747856947683463616792101806")
  + std::string("4450706480002775026849167465505868569356734206705811364292245544057589257242082413146956890167589402")
  + std::string("5677631135691929203337658714166023010570308963457207544037084746994016826928280848118428931484852494")
  + std::string("8644871927809676271275775397027668605952496716674183485704422507197965004714951050492214776567636938")
  + std::string("6629769795221107182645497347726624257094293225827985025855097852653832076067263171643095059950878075")
  + std::string("2371033310119785754733154142180842754386359177811705430982748238504564801909561029929182431823752535")
  + std::string("7709750539565187697510374970888692180205189339507238539205144634197265287286965110862571492198849978")
  + std::string("7488737713456862091670584980782805975119385444500997813114691593466624107184669231010759843831919129")
  ;
  
  static const e_float val(str.c_str());
  return val;
}

const e_float& ef::euler_gamma()
{
  // 1100 digits of Euler gamma
  static const std::string str =
    std::string("0.")
  + std::string("5772156649015328606065120900824024310421593359399235988057672348848677267776646709369470632917467495")
  + std::string("1463144724980708248096050401448654283622417399764492353625350033374293733773767394279259525824709491")
  + std::string("6008735203948165670853233151776611528621199501507984793745085705740029921354786146694029604325421519")
  + std::string("0587755352673313992540129674205137541395491116851028079842348775872050384310939973613725530608893312")
  + std::string("6760017247953783675927135157722610273492913940798430103417771778088154957066107501016191663340152278")
  + std::string("9358679654972520362128792265559536696281763887927268013243101047650596370394739495763890657296792960")
  + std::string("1009015125195950922243501409349871228247949747195646976318506676129063811051824197444867836380861749")
  + std::string("4551698927923018773910729457815543160050021828440960537724342032854783670151773943987003023703395183")
  + std::string("2869000155819398804270741154222781971652301107356583396734871765049194181230004065469314299929777956")
  + std::string("9303100503086303418569803231083691640025892970890985486825777364288253954925873629596133298574739302")
  + std::string("3734388470703702844129201664178502487333790805627549984345907616431671031467107223700218107450444187")
  ;

  static const e_float val(str.c_str());
  return val;
}

const e_float& ef::catalan()
{
  // 1100 digits of Catalan's constant
  static const std::string str =
    std::string("0.")
  + std::string("9159655941772190150546035149323841107741493742816721342664981196217630197762547694793565129261151062")
  + std::string("4857442261919619957903589880332585905943159473748115840699533202877331946051903872747816408786590902")
  + std::string("4706484152163000228727640942388259957741508816397470252482011560707644883807873370489900864775113225")
  + std::string("9971343407485407553230768565335768095835260219382323950800720680355761048235733942319149829836189977")
  + std::string("0690364041808621794110191753274314997823397610551224779530324875371878665828082360570225594194818097")
  + std::string("5350971131571261580424272363643985001738287597797653068370092980873887495610893659771940968726844441")
  + std::string("6680462162433986483891628044828150627302274207388431172218272190472255870531908685735423498539498309")
  + std::string("9191159673884645086151524996242370437451777372351775440708538464401321748392999947572446199754961975")
  + std::string("8706400747487070149093767887304586997986064487497464387206238513712392736304998503539223928787979063")
  + std::string("3644032354784535851927777787270906083031994301332316712476158709792455479119092126201854803963934243")
  + std::string("4956537596739494354730014385180705051250748861328564129344959502298722983162894816461622573989476232")
  ;

  static const e_float val(str.c_str());
  return val;
}

const e_float& ef::glaisher()
{
  // 1100 digits of Glaisher's constant
  static const std::string str =
    std::string("1.")
  + std::string("2824271291006226368753425688697917277676889273250011920637400217404063088588264611297364919582023743")
  + std::string("9420646120399000748933157791362775280404159072573861727522143343271434397873350679152573668569078765")
  + std::string("6114668644999778496275451817431239465276128213808180219264516851546143919901083573730703504903888123")
  + std::string("4188136749781330509377083368222249411587483734806439997883007012556700128699415770543205392758540581")
  + std::string("7315881554817629703847432504677751473746000316160230466132963429915580958792933634388728870198895346")
  + std::string("0725233184702489001091776941712153569193674967261270398013526526688689782188974017293758407501674721")
  + std::string("1489528881599666874316451389030696264559870469543740253099606800842447417554061490189444139386196089")
  + std::string("1296821735287986298843422036698990060698088878584958749408530734711709013266756750331052340522105414")
  + std::string("1767761563081919199971852370477613123153741353047258198147974517610275408349431438496523413945337306")
  + std::string("5832325673954957601692256427736926358821692159870775858274695751628415506485858908341282275562095470")
  + std::string("0291859326307937337694207752229094018708695195737807113096673517703001997619162841026237527268163782")
  ;

  static const e_float val(str.c_str());
  return val;
}

const e_float& ef::khinchin()
{
  // 1100 digits of Khinchin's constant
  static const std::string str =
    std::string("2.")
  + std::string("6854520010653064453097148354817956938203822939944629530511523455572188595371520028011411749318476979")
  + std::string("9515346590528809008289767771641096305179253348325966838185231542133211949962603932852204481940961806")
  + std::string("8664166428930847788062036073705350103367263357728904990427070272345170262523702354581068631850103237")
  + std::string("4655803775026442524852869468234189949157306618987207994137235500057935736698933950879021244642075289")
  + std::string("7414591476930184490506017934993852254704042033779856398310157090222339100002207725096513324604444391")
  + std::string("9169146085968234821283246228292710126906974182348477675457348986254203392662351862086778136650969658")
  + std::string("3146995271837448054012195366666049648269890827548115254721177330319675947383719393578106059230401890")
  + std::string("7113496246737068412217946810740608918276695667117166837405904739368809534504899970471763904513432323")
  + std::string("7715103219651503824698888324870935399469608264781812056634946712578436664579740977848366204977774868")
  + std::string("2765697087163192938512899314199518611673792654620563505951385713761697126872299805327673278710513763")
  + std::string("9563719023145289003058136910904799672757571385043565050641590820999623402779053834180985121278529455")
  ;

  static const e_float val(str.c_str());
  return val;
}

const e_float& ef::phi()
{
  // 1100 digits of the golden ratio
  static const std::string str =
    std::string("1.")
  + std::string("6180339887498948482045868343656381177203091798057628621354486227052604628189024497072072041893911374")
  + std::string("8475408807538689175212663386222353693179318006076672635443338908659593958290563832266131992829026788")
  + std::string("0675208766892501711696207032221043216269548626296313614438149758701220340805887954454749246185695364")
  + std::string("8644492410443207713449470495658467885098743394422125448770664780915884607499887124007652170575179788")
  + std::string("3416625624940758906970400028121042762177111777805315317141011704666599146697987317613560067087480710")
  + std::string("1317952368942752194843530567830022878569978297783478458782289110976250030269615617002504643382437764")
  + std::string("8610283831268330372429267526311653392473167111211588186385133162038400522216579128667529465490681131")
  + std::string("7159934323597349498509040947621322298101726107059611645629909816290555208524790352406020172799747175")
  + std::string("3427775927786256194320827505131218156285512224809394712341451702237358057727861600868838295230459264")
  + std::string("7878017889921990270776903895321968198615143780314997411069260886742962267575605231727775203536139362")
  + std::string("1076738937645560606059216589466759551900400555908950229530942312482355212212415444006470340565734798")
  ;

  static const e_float val(str.c_str());
  return val;
}
