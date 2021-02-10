
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
    class TestCase_case_00124_asinh : public TestCaseReal
    {
    public:
      TestCase_case_00124_asinh() { }
      virtual ~TestCase_case_00124_asinh() { }
    private:
      virtual const std::string& name() const
      {
        static const std::string str("TestCase_case_00124_asinh");
        return str;
      }
      virtual void e_float_test(std::vector<e_float>& data) const
      {
        data.resize(51U);
        for(std::int32_t k = static_cast<std::int32_t>(0); k < static_cast<std::int32_t>(data.size()); k++)
        {
          data[static_cast<std::size_t>(k)] = ef::asinh(static_cast<std::int32_t>(-25 + k) + ef::euler_gamma());
        }
      }
      virtual const std::vector<e_float>& control_data() const
      {
        static const std::array<e_float, 51U> a =
        {{
           e_float("-3.8890825289988327803785919617090243930779408632548422510994962559541730682935115124038376047545114840807234455746115644321321856376532485159765169800715260656887206662824529480393317319841458778158154038644316964260230279164146733452618908933210276060953039358499305528017505013557163822511055467050764063780676448846084650883020224756281478268205217749961314657576347617773831242109107434640015098116"),
           e_float("-3.8473117907234262226321312055423727632132128844008166517282492026994571568747680052990624492616761787851943628056774959478733314695084773549015987207614841626977639100658163149040374073942598700980529347247986691997288308249113040389298944088940619138236386641640308139768597475361079430006842488071808354697993553817971436678592964402663364976315403867295797395908435198268669333072927052222296649759"),
           e_float("-3.8037216439577981200258254710593563199638574726215043811221373471152980897326791210869486967086315729858228380236039686054896108809119833569186144320968507336646720119475943557894679162798969815010971375538834048607607029474608158746521949260408961600351181179936153036300715143113026716989661404905289112426885442273899139509319250585283881388264437861744157274129966801410148615164205469551351948992"),
           e_float("-3.7581465188263482703957871265561609405704999664600540877367857714868762206811328982514321230073128405413128744669422033426386836576998990047219333137008852262313198509541119658852833817171428623759545776632173964266835757460968608690438334485744634138293675777505992657633366483861657032879803536344244837296594645307255357580376580085323291022393293297881631945879426788524718166710264746981760495525"),
           e_float("-3.7103971899949649315427309272269937545009294059675841908620630585004904166999900620339021608389797738288495121511332356020962425762460339422874569213904705816107067767145451037027874778051255249850254509040522316764822709532529685570924340429836331211026600418456797906683665956887077737659521800092446089461127761585134770183220083145925216954075621055782756429505620345885639866147450443175662148812"),
           e_float("-3.6602560500711496446424250323818946857222530839821149816298854134973792468073869926185421240258274326255030690015331821648229742541251154048320032148947466221090857189608718316257196155256628948041109590330169753981058732354476800358383322987255108069939952520754725939037119920248013021022341159189886881889785928946970741659781581276266430965741622979634693877121137331377138527772457621151621777793"),
           e_float("-3.6074711418870998991075912033937588394764842317158434715258814223023456711767775723091762360122700218724047297331597036756428805906926656096524189679539224501917713069288463096085501633224960070364185338837204998036190614161726757802694819376029656912120350400574846109299022180640518172004585011944273836516680310838374975961608939939996782662750720018646680789323401004198584162000257187836431789018"),
           e_float("-3.5517485374724196198967133758567266166398624558675962464356886146987823377159718952143429220491830180769947750029501235731526456320063464369768060000427819219085363873323156083136036586795765638004113052507472520517911450695671343810347366935405641032169998550268765156113172557078211130023784435385114034079233439164237942131740611832363022160753492218508488055244162142851843066375335812365691723611"),
           e_float("-3.4927424827128106305101196646224055133218660286762616559904963208617112477337168360622730146000326433047792537008038848740371910456242671207339212420320646408107636585696842464579927395893761637534748900353454794793834497977216579663814567539314781848959848500770674841949805009865833573626112342646245396588110700812956980721233422104350846437247662445721151781654690819248832718798789356684086157478"),
           e_float("-3.4300424741081575508635465095697725125186275113081645938213872495886495380794729045562217589048271328184895649460824984149679406990575742289110610715349635826061733181065442180891964508793389714784776208463553304403925672698417258500242197711298613319724901627465981420654489886949624925412939721986342037782223298304334081118779435547506137381323166395371970162518759451928959793546922284704307628808"),
           e_float("-3.3631560479289074038093724319194346433489479614772958563859510698328501098136820802542667383264981252711075450580698126314384079157002914462475703874967620551855325417512979846658116789141975671141943967828992249491444569684489475836377467766454037645672824293281325933921176693177871552298607958005257778175452572533950616621300478034750983289888060084131803792455152007233963199073198816441551112461"),
           e_float("-3.2914854575906699215441972707821127403751948348148198227162404133597116997138083092839137692228034452843852373953078365605650496252858958654442475945061575794495790207939657294089321533883349529885816890802462921545539081097142352362906301267900933908325243581752572081389911262574938374920010363540498027792569310481734879354221598647093054034422188709441766013367615273999080576286407932006256076238"),
           e_float("-3.2142954431457107772301709870318334506209904679221290883372042025652216205740175615134027718790501035716662985253594845555582740566717473744627843010116394166595186066609434089975073451976845829558829238245054749119057959598015520595644665748622570880371690571884633211465745073220283594561856519457905311298399861366790250263359370299680253908828878583097800492429459588576268951785193621932659523389"),
           e_float("-3.1306676864050071296812446217913762412129083210092532320158711199109194618970212217221577250618383995147147594503834952927686397344065469029893398413259345232650669659409156811431970786388574790788261160874026304571740862843521630477652058442210556013269532388445482238074680311168389504096308784197233617073312720334663198089311981227880815885916085550048484176425725668546796341717451118373736446456"),
           e_float("-3.0394347844099613249246697028559561086385525257257413120238282765262888611328299093415299067944377437922260446099901944421843434585167701439419503210848222131455216412399810644224320882907393622032037117657277527094237641696255525092697660133737826419268891866948179270007579524501412453086746047108688223722131596166831761611992880527781477664123192199648937137216308986949263702047746647993305296393"),
           e_float("-2.939081652724128404984027738857533676752702618080317548824968475806964364166807070951656348984449950014680066169603499197853314257670059000691180546040092360862247585977359430856129522876866518101805385453183876022326977446459878279471315558720540285027544548685432137470249713440863743750546370681059177917456350590363748342792057054556664579865448000345241084663089345300542247317489009762564082431"),
           e_float("-2.827593093722150690072104774676512901908503993530376404542657605757887237203545685295756115467276305481546457076470534535936034336681901938129997186580581616028484733667610424511746790701258774434639144679085961979216951547211500374479310370867616967295737295261635201244523174425148474041043398734509556317652491408603555429892890285305554340254327671934713598787617383170114438701818117993622002724"),
           e_float("-2.7022082327368826785886236023742064579305745265224386133307705512356997391125786361611408003569314618126563326709696977543532406503048582920193365723907417524305922573935361419872548591658416276623574431372096765530653142475564575284907562767423251076453431005259357985470036241437891358483007410796036269016367265868148200450302599456252982286713855863655817726848225960189934560433062602376420808481"),
           e_float("-2.5590048298931571579021605500420072558148093850773010856772992278013087978644594630334323877541244355508923600929029541791894508258403393729985985293272704944266815407807555265876042799654070665952530098802398834055353439732662920958817112625298356754937923719808713937898112467048095366185765654704476750231780627745019003142206910342826960566433200606759612720607402467132547912270452381657094717137"),
           e_float("-2.392151665238884216469123347448481794563650077474466438435471541214635904116413775483505588369513524621390446352343735899162470916170155879105071930139265693609209563380496766610261186254994211717498501655502564463051402502174502740539003963343991248498854380502874830806348903599457908049363589603781867600849591514316282752517496385251821922513407134289976041760553521139329592347378331749909617077"),
           e_float("-2.1924588581429163453557079593232278552883855114054772148728912995855114545127079544274737527974258926101267648849973937342787237299236495735887089333032012010275813638832924448516632259935979763353254751858908137604675509199389365997496890344533042538643484587652432752125991843509339875875488688695438075617097050065901303240431475599611670718789557066312251305673480403369553091033794847489196067664"),
           e_float("-1.9442885013174948630672851863271854767225249647355828966531590140655816449966056552291360795739933083696808669897448634330218332688519032717017124094303170713771646328946563948564309531908746180418600017959592146864186875398446012127490756537788346630275755045630564547705773959887105778061931432589529222435778998430115314566615154653732908493740484470798941331645915928451637441724485050212807251118"),
           e_float("-1.6181658486507841023509232038731581850366507799047017672988636743034969418401465496319258474604616313615584151138663206600833950577830906566878590656913491852574149283011380032181144298637467164466631635195222691877591099514651023469523057881007764330994145734602325356862429133802826591738300387202674782303541687165782298546684943627841369049112062185947165815369720123002115766936594979976770347852"),
           e_float("-1.1511541965070613890956982342504604663278025659845475110329531937239006225503225497596246752207532892802553735861633507906981867073453430317615074030464086451667489584061070085935503141356775526992667652339252820893165512071833171565179770798101859107098979240740264535128087566112690419892131911245212164804164116566490575035970360634254313525017080309731025761957554915380938633575924320472199296748"),
           e_float("-0.41110603748155310971818866552244465203723639135734044173390922931068526953111343073243793086677333428521566908983285016789000094834366866488662785412593451124869634190812442704703468570806404263540129361867427431801883054675391131969246683482384920531530522293989006929906159641491625493165676744212617544521588641965102862832733786794645329764953746708112605926089326424383536233789088333136776930517"),
           e_float("0.54918957020399014898609193620979185759645726298116552291468817198091742086855538999825339726567197542428672017412670239543030684827635485696762122660884005777069164461218265491487067551591092612110491136766315298687372196052747843536414190127272007209561229810421852073869110205078993102966128457067419288211739086278316497757510107774848001225343410089735136677353528070578800693576218278806526995727"),
           e_float("1.2368454851087754989924007579745093363506431933649374186108296098277035308067875821699820299478210234818185703402823886127338983812910672287259393167442344449947614189099169520553929630041782255946838738237165599701393887656456468022514153683136514217564344844107078350397730502142668792627936920850159954034520021169082546891486722445361572410939225703513448729753456355408488204069288233306519353057"),
           e_float("1.6755326771946324337094153622042609164779718733803057199429220189647032349955914914294307746926998583486927100008591408585558533009527679391213074356290893172913228204579299327568017486237543519319798638672903133310693639369403358589189965466200331706940017990555637242332516323897530109796862183162136361754733774741403020757649632643874747745041901518455559711777778410744523354391383175745788611515"),
           e_float("1.9867196947067653249250727416077477900441266263239000050026882414209675745394055162691021480980712915537404289421875821310277574625465838843648982014025489341919432035890078924738452356111871361256129247412888800056162959356110825699487424358162878610226750188196519200273022364509152195251958802491347117476365619853113123233367386509232216452861067456963423059277279966901845495992541462862242499153"),
           e_float("2.2259626296498290713323941088321856646664159349330153384658456959331368734954421946271358977644517575215045820198060687720481021081213830307870924207205266748126356843611788755864331644018371871689638927756211447644882395506807079094443216747136071561293524909200235885897099650522987324128050346220550041958417397822270249451804353419602967320817173589500609256969862782771272490074446256225636733204"),
           e_float("2.4197788540923901466784525544068485296452644844982369684703167819390347655642619183629347214611997949509702774253549513774799268009281724177495358977357926090561693899795578568678932456419084025515805428560268267975336802460362225269515144057912421843896427791977798622119815296286615591181115744954400676503778167666734313126146332958289122491090392585777807843844587926606545929949195038186248811242"),
           e_float("2.5824882647792486486497487506645197610886383605108961775624626556033986564978624856905683944029929480734123704801419089941739421021020456171406387126567394667058172912331225313923892745232370264715106404098096773496750864671531125808268081477830655561968502588223010206459436699359417631523938300079679945432990299050330463620410135032577058625744336648744829541190299648647238784386358372637977283988"),
           e_float("2.7226191417941952113742025373789018530917621589878946105793131949729678828761019782561150150005089133861098311618019142833966001459580324623510947100708042291352118084238482856141495648145180020390249842440683723896059623123333904240255172527352425231057509890759271146020682693046671171259593308083293558681521129814966920170843025190773535244472732230727578259887666973486623222041829456919394540067"),
           e_float("2.8456375225254230081879818057401564283154768658655718485933086693401133343585389952244669281549508263951539562483285099644570445359026922054561618335160924146326023545971628829654654250759576541674460689608033635161636812334641110108546520239157440053010641100156434840518653178134625951896303651267719708634887693866180776174335527391527756078149276670983754794389512149520734727497882168377028672879"),
           e_float("2.9552486095402046086418980571316681064876456513875446370578466114315536170459430567380110859501793705609574997140658914731439595482761904596682263043444320630390037668161742546178397241680634958297215927906091930697213893014317233343079538537364757603118726657207308272758569039014045893654712114119636419760596853523082867536617368826600517661683148466074152011457927870308422062177520795306058374301"),
           e_float("3.0540765367054653651283257246697137043724802245812168074486254489237531238529730380294711298537815510380633515702360735015089672878742484238694932961883026615333867865364407341678735020875531879234519411715945248810580220225431022776618227842493425972797534865717763497047852395280811974010708076901889128368335990208721530172192128905462433439147037806393019911698443010461162527974823289267293870489"),
           e_float("3.1440462105568496214541919509906031730125771902172119890274834234568613600666699673496707876749550278292650198278928798778861167515965428061500312181266312795002475651290555766250998867137949221937686452540719310721485510039412285456805219207071397072974678887287279123632167127556290722414550968403596981516229211649912881308018481092027214367211857365423584852327737837722091525638452529871570853878"),
           e_float("3.2266107580333979663622045255046341875094725924836229970756208538526090082171541948757738276022825505649933776957717126042176544763268501921618184106223001485127929398644760826497824485440177156711097873010172689977137243100447144748893767745352340581610331111154905453740160714093195203018083667176145830593109243663379045908575649907497164743354993943199542029727955638301596945872986004808189077015"),
           e_float("3.3028936829346253417509247505214126070852695442431365186030295834129958927539096386283068778232120239111584736947023527184346267002430355310916819901481463981195358297681426164012134632786705954615921336140999335635595407146755470599378942000849562107171337678266604955619300683920085457644771264069454772648305343349840199359370979264080702107588205890645466145777945581021987781652845175596575537491"),
           e_float("3.3737813456830175928547007310875705593149713430416390230549600550048162164673650274588442047192016482159164968655767730904499448525562051707591335241726271637798940366625229505734827552153502910204441513927387258868181616483764409338436004599999291400530756859997509646692007900274032370235699640874217893031352044765270239192494546378344382870374321381417473701057379849564819761667427276298424731678"),
           e_float("3.4399851963146166038959913511490056686357076071065470778855560161581852012405076594974840470501526979088001358046475406998852961025869947523994475780436210019222688907815118191551894646660488492142034972174948065546887894502450948289969961694928862924218794538044254544697884844571970637422371229771753688701646313554077410486838614419677730207152488395367774644804264572224001711842197143427977630878"),
           e_float("3.50208488291431872166979725896858236360824275955266332551232293762332260354079671623406263819798436732367687961537439135773758599345532194003267612297114455355046835356703401170253116305365709300556196846069553063803590534546964914242812266783091398547147765169704507352321515516224565998751885224435761686456851095561276250707389575796260760280593048688790043272661241447546456004876551189589164771"),
           e_float("3.5605588692011925066243664707173283336889631778951582205124058155136872308786698550344532249399367268411458687412860664985643024651413245780200670687677606915526586789322827596304456882009760664790954215521777226315093596650550150290751915371891653072754046702671262367461206323775771484130694403186983579803683537123842869826813037571200635749404206646022109807338033212416845116033206981875692369854"),
           e_float("3.6158066608108374328811375597040790398974946311472062967079402700433979761958999386568467065236522225650942251334158253022468763195660424179162394081253106034329021667319782613649642889183345058086767530713292178994440318684908887222871864259552633499338580104283505952368022021628353320323712902460361546800442623068286713855561037996133542662303686039665344440393744882684850946311010851370851466473"),
           e_float("3.6681652533917685037872454484556867029444657143534167644705408394165921350389151588916367939920041064334701537019624295815879230886631351778411154941279047104446746835255280428677645218052540818646531569616745964387561943875158137941776019876457513200744543089202275233543733991686638513282535323417254966672985291291521820747549722826180581245964962687857230086421701576259050541278916849681552482588"),
           e_float("3.7179215141291383732877968088875752279580684266291186158010443462927555849929870131732320651339496436392488064103777708313053515049971496610871738841596751234904942651679274041107542581829409806419429218870988655216044175644044342859562417424699346272707025639309290811463973648946308916628436666442229030143770264704026164050274852604483003021225367190779486629877625916019346613312301133189418006867"),
           e_float("3.7653216451957785608054806849686190665053569038353114070522759531329021825532700382343338635085303811699525741081970178611177746993671461326404870284731210194405722608785924524125469106303084396746121532808141573671346804485477579543883926775439897895004378523364163282592664101856572754598530844287750850944132605390081942166853384311683779489673348310830141371456888448848609083794822402096563577846"),
           e_float("3.8105785165493746286093864606045372402198025315208950439761774274967081284632721991333313444130964620783685332035263503892260898002155612002169073222439625286081756582513150660994241656397023259860539266776204291171717263758882229753355959064330871721658444132415759608345617363675949611506154379467425404760185310308188222771347622258086404021178743518813193655935121940148832422116506818935028701451"),
           e_float("3.8538774184695806113031416035059056173023589579250067818003111099395976753272782507766454261524066957442124319623275155275386076957373433663203603654245284674263410451210020635028097510709007187609818867363857271707831386488499270531416814613832940864579044893954292175962868765387783022441943977497314843424415974127263633304430005025393128097008270896619738288250926408641276182783619360951486215476"),
           e_float("3.8953806253217937520397327556468497630756748800631519759311154950420760887590737971893573420978874684914074839669268508506638734860807949511356180736064346041129126008434092271156668421038537909977500784180324182416013841863143665964277952673578956388930001392184210921161191802831491327024678561433300729951852925506062228527695201248829665342583467361980072513562280185246011118054348408667936876283"),
           e_float("3.9352310534474215500155252495492614838978723091560986229648569968874247051929377631422641379139414230399289887451684946589085621771544385525561442444514849705660234859517224317329711416529434347653434002968554207033161893266785842320625804342971802123480142236896347750284608833616965326486415839592627816286373522934458312726738792462169740218937174342285917468374806826871218767352821228026742142703"),
        }};
        static const std::vector<e_float> v(a.cbegin(), a.cend());
        return v;
      }
    };

    bool test_case_00124_asinh(const bool b_write_output)
    {
      return TestCase_case_00124_asinh().execute(b_write_output);
    }
  }
}
