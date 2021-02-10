
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
    class TestCase_case_00903_zeta_neg_x : public TestCaseReal
    {
    public:
      TestCase_case_00903_zeta_neg_x() { }
      virtual ~TestCase_case_00903_zeta_neg_x() { }
    private:
      virtual const std::string& name() const
      {
        static const std::string str("TestCase_case_00903_zeta_neg_x");
        return str;
      }
      virtual void e_float_test(std::vector<e_float>& data) const
      {
        data.resize(51U);
        for(std::int32_t k = static_cast<std::int32_t>(0); k < static_cast<std::int32_t>(data.size()); k++)
        {
          data[static_cast<std::size_t>(k)] = ef::riemann_zeta((-103 * e_float(k)) / 227);
        }
      }
      virtual const std::vector<e_float>& control_data() const
      {
        static const std::array<e_float, 51U> a =
        {{
           e_float("-0.5"),
           e_float("-0.22523583507956141922689330800104608893914785333926427668857378643762935790424889895690894514440089177472944024001455045464617351652738690321930230561492723942440381858493808941367379185689376094847561119266530532570027007359453628782866760957348811700415077210295825947326315915971151687287954342400694181347207408653173269280377246889202456004926405201689825284101160406886527422722738750641428613027"),
           e_float("-0.099760141128788115944686922186900613399141573562129689905149037956739454976760452278497051490809407344263431171470861554749369492025792939489191111606695768084264480796090607661650054307478413077274763850341693435152847321422111074854717010578148117973675598782970069746434219665422613974379719501515215608505662052979482550390886079117869040464987031128916244953886293882547917668588780025763034497986"),
           e_float("-0.037345960353052820779839478563982744057912814931901643369517525801522077425812677992845464806546929744506283646267654462855436477287352873085985244519833961340706013180243603423724710547134159366654980975236011268130858152765575988710748951239720430714331927553957874085000436327980573278734838869218672902259460640009981492370226976310364522973549414151925708959015096560784015663484460943349695017619"),
           e_float("-0.0068522414190441060371127410646685668273795111059739757809958141401140896546223300324850091613038812201988360020365429630141692849506256937902839318138285832879277027891617708251964303180028595475797662854000001817644821261389832559073384398265920539828853913695535708520058095199617774624377556040327912423656626292525570135808984226849599478895268979263137586691078024251093330449309146592186904678748"),
           e_float("0.0060571977266689039218489584867039172652000626388394208442226740015463037796530536593250559861240126027707346296560197343829368802470924154978822894662452503446887601080554728667453456452492835222834626905965590926853705182238061380679195430230801447349054206329719713905748194994412143141171204745855231677174440466045253140969662858388380076216222263042402791582496799599396158054443191978819515922481"),
           e_float("0.0091595632630669387378302002268114321895012117778239703609738236439949080306606235004263352158798706836914425502874180583931345746578083299683179107170408631464254074609908412072179047098990892432426331915387205447352529066708679688380772580195266231024824916220835059170628179182331280781777332750907013467233130103960947738738984690508932667847646219336945376122160948002143093893058540440437492997717"),
           e_float("0.0071913718898648449672909946117902957983088353549678948818240119616279810064778225454597907302730296020892317259759804128258892033437554393379089083000610567589274271009837090274077427224641162930414214982422142109504530417920383100100174064438237470131958367246774168351971420495130852591930830014228399385693676257838889388136284373704138658178336692260513963377070883081561683721740008854982897397185"),
           e_float("0.0032432069259099529347916738537320501182064757649865551929823439474519783715854183433515632203321342640524225919624252679481828736028981555491052389291994189978094583214262051957054090004650423304739204792505187674792115625753530099110452892730146626588894787024276215121872858443571359864656219664244033545843877213668196095406324271130130545425862420435298305019895695300504992064376796022063491272368"),
           e_float("-0.00064713105166791278235095760407401431617647625939337252084564106927571277562048459035997591177495861162877735284197037739032090229135947072861632102544505822865970496984157091182591960466024323361324998754264725481802714218993288948567784555531159555678971684683835150079638799344579982184532609781131952244831974256596082734377239681499217897130093224869580793313749561612280200157463386839653982793174"),
           e_float("-0.0032386629368285903837383212247653553202825967698441838730548653284495857411801197786510922986681119901510141719810711514580620634029125580786916753187866862280630256961256317808259631290878679112697969727991528831753133681298521295087181287354955749330764465919883379556368368420236464421270729374229850972585307248723552615132081379312614554825252797282730448065098321455661922055290010218822245279842"),
           e_float("-0.0039729544688050017370358699254983632200454764192944699239033244616295806214545699194298158289988600539163560228097135264872192517083485658494072795233042800958663593103959396446473522536183009802056728297478805535462483160284594239032798319522812197586648945063988477824727822522822190430253572420972818717414648210427459396866369059973624230273087893308980472552535154759342364677977783399177648042304"),
           e_float("-0.0029015742850846418642281878809557527276118072920882047653696706880150133998169980422668421097316672044618294804334684348640407357674579899010083116642547921869574760364314590701767717683835732263301651845219874864117183971235241914867003621220004607618648282279059451582549589397477450313005750019523907330011312669367494330902124525064161943955177163433501675836600459634488006948507255479390449585256"),
           e_float("-0.00059399479017800853959790243593155650493032215203386004966072901642262036480030824591158102190041173037123820181732828975610944948404390058245561626585856065623180928837037717037548587361413362284196767082661663041809322260948848872209571903196017349791294328076196050653586147861940981241125709278818049570308479435300073203934079210305088450323129728559653726226788269512145661964633197798277950935441"),
           e_float("0.0020141396439082575178986109780277906037565655306797026031043297117719577817114662500639060965055945036838468576477638902235776840328403587120904483660236616558803945618871986230379258636586529921277033867577965512195896034863729631662099454837838421605250320465918653833953434890238680221629437831007338711699833981504728834873996812020979967841856224579414143789074458544127961925432892146715238004778"),
           e_float("0.0038524067215349865001531100984602060156492993908022592752065285031104437011273841729805423352867743101368120314460005603784568384544292807993261182274230232428017121999181737542737639983574178114329025908047865488698532819202745357586480881168319876681098695615538767462851288778470443643499285350276753176103423551460342285314430533207752448006876681264094534955425503820538124243620382851424880782223"),
           e_float("0.0040201332469242041765712245591227866450509686132692092422163860667566469589695542477664125944915707553575604122131424702917348521743488869703624938023623897847871594387928991069103589176782375590966880446944196390854682755124253778106677252022244816796278453169275991863835592836871562212672421078538807875364999439828184661411598498071606865318767023014497044358850868322845340487573626340657408275931"),
           e_float("0.0021219092193264222204264823165509083232159101850734099563012169008462369659206296483790423363972853903638524850930305815463701716957404925137813283196387120112912608389258653872965060287940285368962903788382758168501717393994917643616683705035556781918080995675909666995963230568397374493546808898152246224513118167107594412553301840166220916579240110458583683641165593883222063549437102174183453936861"),
           e_float("-0.0014497369604556535513801649804229099166083734966554632471638350522770817989858930140978123047199249367091222375214816649931701916815055817819128486643768753751925497910853729679103963423859830918027244256630288598518213777620700947733862300065890621314153564808409313230721248092543872627346490387801421637402961181208063649284185877327189954887752197696983368991121499419010463341220504522903241843054"),
           e_float("-0.0054058072902780096690915046231372576852831861653370398426923503091225851187860883130337337660978055501489166995466084855291517887265203378835822204824103316485042502641716735742426007472762171428278264553668652383893587621997989352648743834907584737929654211713444729022108796597744823412286366081014729384774060063585672290903391457686639477620392564941216645101708914816167802923279664171183886734758"),
           e_float("-0.0077621283398685476523626231543112976141387385999950000282448522317650061235056041033458557828473581948779840200473431661569331497969422467812944234381230473075068950114200673122456567001279060600707822756805134115498144677260379766925474196816748795485700942030332065979602195741364682534146653686695515099042603322242923628960685431074238392710625899269213871598059952568024676643791468021231962544467"),
           e_float("-0.0064509389640070172542272152792091607374461337023002416563095751760098616454372968400465150987251718682131274250688765931575094918431168380167796087776345915685888470475620806043362304412008313439575008858963161205273677919437585321226198034875604427822907411191278188907271780319656518383455437725774834583088005624843273099430782941090330591037369423227749251938521285542900203200859395097550781494909"),
           e_float("-0.00033052484335383809535283673047081401733897769164865989348358482658026730136607165169485154185644655940894978886730011660468974826520518704026156728762631412361799642139503729968737785311880965518782180767316515723732951636548591727280075916700676545769227294086112153897283674046866474964835594157516038880839518922525771696769389287326263632337317521949386197910375667824610264461894566230762001698215"),
           e_float("0.0096248262739927638011114019185806587912347554571991063294186260969246207460973429673142919058923222991701321669220673818500487212590595315317410374316532926833565774696745873890159646789336912556977758208186503706335717523172243668344604854340217184998085986571284177597550527494922888986298790464448953701019161639305917552591911423065981619381377837250914684336521875108932716972030178281639009233115"),
           e_float("0.019449760320520916178628782936633308047340439902428149200184078040861015868407042314574976082180760076488908348146191234260425651321548984348519946085606804463303461224801612192831409321720148574068798970538658079575690670375817170615428582542414719363155928541596270625718609500205275171087067986787737664514441442446587766662558569669089497858440459619957092542941781831407082425390413303274685210397"),
           e_float("0.022385930520541946179777318519861591196908496429327564080513706759016378349174205943755983052998422414410778094551487670755961297175199647644797946043742742458875765082009807286704175313184098084030679153195947036432363443710102689397577399369166744145707076333572988255501692753211193496563443610766315498388419452473203772942341550044903110471922598013014391956723173225405955684778466560857398034174"),
           e_float("0.01098350141219592907222321230280429800951585418187100884699799131328100445704559467653763638272435585737141953897175367511961420095256312925544209832355030600809716890761940188140646608579320408724999072749009730488470717689690969405974855681542334994344958046730623290847526236506685070029224682725953134048499619824593723727975220656544375099194726382856620797950147918878175274680597510557835399595"),
           e_float("-0.018443806325506055902947634919443558397386675821560865160698631798438901005347764650592149551457516190067738175001079320029621830727267179245506953648618602004933363606676192094725058298202116202307579724097254792147783201407255080144916095960237178516754716112650608784475911309544875142812205546069335781949815068668085704931739125708784981874833139584055415739224916663331991112555580344542744033698"),
           e_float("-0.059664951298426637429279589510709118417405509817925328222829648966646717098584491668489930834784053929451208342822647347693033699635219671121302570075166393597021134964680634937050713830059526592386764043250037106468832722994889233727396202755689168412940141576631104241266854497681080731601210588932136734230582742634978113002901251121142219943757206386414340372270063569036945967363857050895767614539"),
           e_float("-0.091262758376340711039185182189079064732080957918840845627672462396082152752351472493822917683266953965613626278174391675864110505296041983551824175946751156655961980200936400593154764252241093979732549926137015912542707429455820560945530471098114666154993207928960000650118406684784200964555984193629650430762997451060667478852557329880232909624261579250173046075745557176430211909288879939754643085831"),
           e_float("-0.077196151971051904792966954816141171729087463308105755316505870510194247918757844581569390880712661518607215178906648125573506049094262562835099853954697268472904911967668545986281342249362318395429053749488505926258000003596801475606393690937512066550546314836452398595025780757123953566921872170769110494518888632450408902178119786917730880170024678352512134579130556677918125925966600759364494015702"),
           e_float("0.020334258368109218102577872552330633997916842195993729605853780030120383680360831187394856980040984132200544269890295197974760726436816474442234204184407748268273516635381770035476427561505705165973970563412632163577029954651985873915448880357421675511215099239744209685894031618898743929403453722605635150656795765189869761067157038713052476745385343416198533257819167817620128536599126013945984661297"),
           e_float("0.21095103617830959118230303818647586010678399930260924812010025813338610683841604033838405134420359713603602850147252727297478368809911567764439393082988920025333644578227903438325238867251043049507750940120202271036550257914078473052926740271038467199753761931110160294449825533320230691167534270193725258447746186285099016096295511136471320390563359240226145530855800473951305570034986001236675084985"),
           e_float("0.4324407355607316531021372688850619233227869757340477448463342914768158541815475920544101222696281278909155138279114550371588206356830439998125650961404172561513805060518682920085156935083573128117096138139339682728027199332585019675706450018025448463905902499962127462553012034637840022413008555996904431177108596441201715253006754984009509240711375155781398831954825198382039405254692492017462016247"),
           e_float("0.5135595798240363013862147198268348742487076016590310348264818917617800617541330342777397248052871178498736608898841031428531557020023867718725146201835619353096493413413714537396352923737424396345228325021555940052368470043162036064027012517581560830566381624364022437345433511885774974753036991718997972430006019393421836700453320871895374394643191052755842290733045304405463525972185770269159729577"),
           e_float("0.1869946153389306530361265443431250127782662960433300088362184095397106712512021630227122196222526948722509060532190138468042015824500600969141172585978470450930630861952189819757871382400460825383913427159813563823707774666863716081129862300959277956259177237979037343960986915785803712451283126094044283950536324033192630086844338940870026181918902504620120102014563252396849047349763980687252894464"),
           e_float("-0.78553541696731668055788573543282643759245706331767422777975062791252496229336699991740176733450263418205035363712992103237375847138569298538403396507387378187093814510591976101506603054595338341559175222353385035337973321749174380849273752703025662493457448877617512440780091769042289231736233712699988542080358834549671732504447329098939374143951335917874747521726864641892954910758900169843207394398"),
           e_float("-2.3277150022421426461037159843629470822609232418943183694134658911790896262054615184876811502407172464200716085112919226261118840643037145843049540840315417071537490293645089459550068330644022958192371483312054196749400132278687373390240815499996800770503653119708352120065028516790148094548869153217859657438964617456768111084807677278669881296775229872518380227529460047961406250487436622935125878639"),
           e_float("-3.640349567937565540216773268405777594114008333915444835106654700763064910220953700555658055585972168913527229944853511542025339453704711818335492110772886344355751646850349003884656858945333402196203938238053983290488403991607546108110962985732298253295926071120161233961388569735461963737316685369082662735237724213488533109365059553313430816556491348921106877486994832391155716176167690819797600277"),
           e_float("-2.9025935413710599570036416960106637173112553247876769017787446850530877483785809877716937276060470932186042943248133347185711703048405459676048094807045202214068734489899433867551687310280867091286961014084088507327378213913667890492705970320480657701524466623048104091118183981572264764989630062877033448408882665689296885849469603082834428344461708492919875902790547569711163497470269262314374395272"),
           e_float("2.3989936512351190171061697000483039034961368375100523044364987140105481564263757969761860105706911186585245107806314461312154279447206695771172169363060641509050340869031195730432368882270088985769686508323177887788193771587031380814519303592703111596110553005867875093328567427256905749618067724007551596213138509414749768812117166102030010232304278570638979497084822363788014791984469198178016101419"),
           e_float("13.770723366759676381751643693402519717809625582640512375998245545086360826287274059032767203571599923262985616698807803141405313930996128466091302431810471317082391485786584298286789154898005747783778566110988304766313553732037100939176588899290771975537487444832433609068160503437988520028291376171248514939403840284985108838141108581903946392424091273963776954934771343725244633243775704549645939463"),
           e_float("28.117398502829620913842341812088467377118453496494540568289261626787247329057461762096931788596680886020362561947558344907406525537607217363017224137408645854348061025546265982209458554788458947536048280472760873299715550514622615393828159967711709674041809342333694474937170180785472051770352381891400121284670816340643703332535837718992664927294097357578181753838312370162764902736010896961247554832"),
           e_float("33.007966956978580578369009420578811464025681173637631119375750063232246703372737212330325564185857315930537122312148155878956287347931217065159785738837596483438328125894381366868844281239511284786487083394103552530056426937667593940280914953095130166964600181548860826912826879960647030392722217355714015563577718295597397116469759738957920752237659258752723561636077947045219658399382986441344078931"),
           e_float("4.4694272596305907793391992099321957369059099621007334515869088278728086161625617315040932062956290251280906599069211002115056090680456219436054074926482892957835333113155039694884829833686503605331265480121251575371428593052488779757002785654383434794915628287857134032235869886754426372593015339951388491573289850142612807901382716574797719937154960179285563961636283082164587427913310812457061234294"),
           e_float("-84.770335037135220761918415891122949711972160168565818419523791166203974658281759000553242121068409751686046334255837863285863896794249320554198214026272499456562858907721331641274182143317570472088246976628422020854064710078817269335737947080235883128635581734384655346868582295557505734696849266807638158632864241990184265411394167020957668820160104876578357936162928223097271377446412367490047887344"),
           e_float("-235.78700002848894419766305293810155874803344238300740796445127630555177161398752289913720916672939469259947286135403674232669994498264888820783313307194292974443739570079836149085794625206465990828583217261978249296221807570674611026932521542170925545638467353528834220136201662938113204530028116004597587244513848064386869972669193736855245945672643092447562573195171676413034162429758681767752457432"),
           e_float("-367.32040669524278029798626119212825419435569154367184895972204533121033460477690144865562440206551062110403182600551107638849995482989122432482125686863530803756373409361163785702725169507742963977249567705770561385050617962551051541832544719543767455427421232791445494453559949557852871942769870232443534116871216652882168197445216941964141604967025850498710771684299832704974312494279851472736551642"),
           e_float("-252.61481172854904182542387647330969865261534937176953715452720667757313398772101556124855209376337169932238231097575630539877659922400297507959233889344433215188246429918637635254194371521606041821539712950839644453645858650393843816250004012879859908380249347133301543357968323380110321389758380447083073269112431360574408879339009544116131552432392451162507973368473991830772228909889856110102810911"),
           e_float("476.57458949935623760927605869361311532693713735858914619552204662783299533870454836359054014186273380421417250471972446772921035812222836086784747076144750542182459153428114044680943738252707503584614175511697251574009473324277958447420222944470715223207426635016820852319233993437011724618024150159456667761999458840556941015913482229737502983977102023101085459553253478926015702476597299916745300193"),
           e_float("2109.8392564080299698455019644658044825385883376964813959062672754087269970125619711891739970634168873057629916192941015961030922113927626395721250365850946992719102435364000852943641866084520038785026250110727616533057373810592904040519334154470029566679036386587886849821604674124838050384008058246053314500595766794829383294525247869911808697976061270890595553460616255264575348471736179324278166939"),
        }};
        static const std::vector<e_float> v(a.cbegin(), a.cend());
        return v;
      }
    };

    bool test_case_00903_zeta_neg_x(const bool b_write_output)
    {
      return TestCase_case_00903_zeta_neg_x().execute(b_write_output);
    }
  }
}
