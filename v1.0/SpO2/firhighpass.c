#include "firhighpass.h"
#include "afe4490.h"
#include <string.h>
#include "algorithm.h"

#define FIR_HIGHPASS_ORDER	1099

float FirCoff[FIR_HIGHPASS_ORDER] = {
    -0.0065831705,-9.550420509e-005,-9.614052397e-005,-9.674464673e-005,-9.731399041e-005,
  -9.785284055e-005,-9.835133096e-005,-9.881438746e-005,-9.923732432e-005,
  -9.96174349e-005,-9.996187146e-005,-0.0001002643403,-0.0001005200756,-0.0001007298197,
  -0.0001008952386,-0.0001010232372,-0.0001010997221,-0.0001011188142,-0.000101105994,
  -0.0001010308843,-0.0001009135958,-0.0001007492683,-0.0001005304002,-0.0001002827194,
  -9.997537563e-005,-9.963668708e-005,-9.926950588e-005,-9.886387852e-005,
  -9.843080625e-005,-9.798025712e-005,-9.752402548e-005,-9.706959827e-005,
  -9.66219377e-005,-9.620213677e-005,-9.582591156e-005,-9.550793038e-005,
  -9.52753544e-005,-9.514296835e-005,-9.514101839e-005,-9.529728413e-005,
  -8.491730114e-005,-8.985015302e-005,-8.881753456e-005,-8.773519949e-005,
  -8.66043556e-005,-8.541729039e-005,-8.418226207e-005,-8.289227117e-005,
  -8.154998795e-005,-8.015791536e-005,-7.870612171e-005,-7.719746645e-005,
  -7.563558029e-005,-7.401945186e-005,-7.2346651e-005,-7.060628559e-005,-6.880980072e-005,
  -6.696646597e-005,-6.504964404e-005,-6.308902812e-005,-6.106881483e-005,
  -5.899376265e-005,-5.687864541e-005,-5.469620373e-005,-5.248687012e-005,
  -5.022837286e-005,-4.791995889e-005,-4.557999637e-005,-4.320771404e-005,
  -4.080127837e-005,-3.835477037e-005,-3.58653997e-005,-3.333387212e-005,
  -3.07409282e-005,-2.806592238e-005,-2.528377627e-005,-2.23471834e-005,-1.921071453e-005,
  -1.580026947e-005,-1.20257173e-005,-1.157638235e-005,-7.342594472e-006,
  -4.234968401e-006,-1.079116373e-006,2.127746711e-006,5.377413345e-006,8.678948689e-006,
  1.202601834e-005,1.542166137e-005,1.887112376e-005,2.236529508e-005,2.590603435e-005,
  2.949771624e-005,3.314111018e-005,3.683530304e-005,4.05668543e-005,4.434338189e-005,
  4.817563968e-005,5.203453111e-005,5.594453978e-005,5.988968769e-005,6.386849418e-005,
  6.789666804e-005,7.193769852e-005,7.603244012e-005,8.01578135e-005,8.430644084e-005,
  8.849598089e-005,9.272975149e-005,9.701083764e-005,0.0001013387009,0.0001057175396,
  0.0001101603411,0.0001146621289, 0.000119214099,0.0001238006662,0.0001283756137,
  0.0001328812941, 0.000137211071,0.0001412085257,0.0001469656272,0.0001512390299,
  0.0001559399243,0.0001606668375, 0.000165415142,0.0001701934234,0.0001749921503,
  0.0001798173907,0.0001846665255,0.0001895318564,0.0001944209944,0.0001993324258,
  0.0002042604028,0.0002092007344,0.0002141495497,0.0002191184321,0.0002240998874,
  0.0002290774428,0.0002340767096,0.0002390730951,0.0002440771932,0.0002490914776,
  0.0002540934656, 0.000259124994,0.0002641422034,0.0002691658156,0.0002742099168,
  0.0002792609448,0.0002843158727,0.0002893716155,0.0002944288717,0.0002994825772,
  0.0003045119811,0.0003095078864,0.0003144615621,0.0003193668963,0.0003242500243,
  0.0003291572793,0.0003342042619,0.0003396002576,0.0003439303255,0.0003489877854,
   0.000353853422,0.0003586970561,0.0003635227913,0.0003683195391,0.0003730947501,
  0.0003778397804,0.0003825530584,0.0003872405214,0.0003918921866,0.0003965043579,
  0.0004010783159, 0.000405615312,0.0004101183731,0.0004145727144,0.0004189797328,
  0.0004233553773,0.0004276727559,0.0004319518921,0.0004361833853,0.0004403601924,
  0.0004445101076,0.0004485841782,0.0004526277189, 0.000456623151,0.0004605494323,
  0.0004644128785,0.0004682115105,0.0004719423305,0.0004755957925,0.0004791654064,
   0.000482664298,0.0004861006455, 0.000489487662,0.0004928449634,0.0004961660597,
  0.0004994241172,0.0005025088903,0.0005051696789,0.0005084362347,0.0005112125655,
   0.000513989944,0.0005166847259,0.0005192880053,0.0005218077567,0.0005242325133,
  0.0005265666405,0.0005288097891,0.0005309511907,0.0005329960841,0.0005349462153,
  0.0005367987906,0.0005385497934,0.0005401912495,0.0005417348002,  0.00054317998,
  0.0005445074057, 0.000545740535,0.0005468601594,0.0005478708772,0.0005487813032,
  0.0005495533114,0.0005502384738,0.0005507848109,0.0005511977361,0.0005514948862,
  0.0005516676465,0.0005517128739,0.0005516292294,0.0005514255608,0.0005511139752,
  0.0005506875459,0.0005501415581,0.0005494623911,0.0005486205337,0.0005476014921,
   0.000546403171,0.0005451107863,0.0005439945962,0.0005422724062,0.0005406484706,
  0.0005388373393,0.0005368787097,0.0005347791594,0.0005325271632,0.0005301316851,
  0.0005275860312,0.0005248864181,0.0005220419844, 0.000519046851,0.0005158963031,
  0.0005125894677,0.0005091274506, 0.000505518401,0.0005017499789,0.0004978174111,
  0.0004937388003,  0.00048948935, 0.000485082448,0.0004805121862,0.0004757604038,
  0.0004708688939,0.0004657746176,0.0004605264985,0.0004551245656, 0.000449549465,
  0.0004438071337,0.0004379020247,0.0004318390274,0.0004256106913,0.0004191997577,
  0.0004126035783,0.0004058167688,0.0003988420067,0.0003917048161,0.0003844274033,
  0.0003770334297,0.0003694657644,0.0003614437592, 0.000353568641,0.0003453680838,
  0.0003370129853, 0.000328482769,0.0003197686165,0.0003108813253,0.0003018105926,
  0.0002925609297,0.0002831367601,0.0002735276357,0.0002637364087,0.0002537668624,
  0.0002436202049,0.0002332955482,0.0002227817895,0.0002120876306,0.0002012184268,
  0.0001901533542,0.0001789129747, 0.000167484337,0.0001558690274,0.0001440910564,
  0.0001320999727,0.0001199680628,0.0001076502158,9.514023986e-005,8.24578965e-005,
  6.959986786e-005,5.656020949e-005,4.332801109e-005,2.990307985e-005,1.630012048e-005,
  2.524029696e-006,-1.141425219e-005,-2.550746467e-005,-3.977317829e-005,
  -5.423503535e-005,-6.893452519e-005,-8.384768444e-005,-9.869766654e-005,
  -0.0001139515298,-0.0001292849629,-0.0001448033727,-0.0001604969875,-0.0001763556356,
  -0.0001923901582,-0.0002085895976,-0.0002249565587,-0.000241496542,-0.0002581986773,
  -0.0002750631247,-0.0002920928528,-0.0003092898114,-0.0003266549029,-0.0003441759327,
  -0.0003618590126,-0.0003797111276,-0.0003977099259,-0.0004158717929,-0.0004341829917,
  -0.0004526384873,-0.0004712668888,-0.0004900046042,-0.0005089304759,-0.0005280034384,
  -0.0005472105695,-0.0005665707286,-0.0005860843812,-0.0006057466962,-0.0006255424814,
   -0.00064546254,-0.0006655142643,-0.0006856988766,-0.000706026738,-0.0007265114691,
  -0.0007471441058,-0.0007679046248,-0.0007887391839,-0.0008096368401,-0.0008308584802,
  -0.0008520369884,-0.0008733960567,-0.0008948670002,-0.000916450168,-0.0009381537093,
  -0.0009599633049,-0.0009818868712, -0.00100392045,-0.001026054379,-0.001048296108,
  -0.001070644823,-0.001093095983,-0.001115644118,-0.001138282823,-0.001161020715,
  -0.001183849643,-0.001206755755,-0.001229756395,-0.001252832939,-0.001275993767,
  -0.001299245632,-0.001322548836,-0.001345977886,-0.001369444653,-0.001392980339,
  -0.001416600193,-0.001440283027,-0.001464018947,-0.001487803063,-0.001511644921,
  -0.001535554416,-0.001559525728,-0.001583558042,-0.001607639366,-0.001631747116,
  -0.001655875472, -0.00168002909,-0.001704258961,-0.001728600473, -0.00175280741,
  -0.001777163125,-0.001801505336,-0.001825873507,-0.001850266941,  -0.0018746719,
  -0.001899098977,-0.001923536416,-0.001947981887,-0.001972442027,-0.001996906009,
  -0.002021367894,-0.002045824891,-0.002070276532,-0.002094725147,-0.002119156998,
   -0.00214357255,-0.002167982748,-0.002192367334,-0.002216739347,-0.002241088543,
  -0.002265398158,-0.002289713593,-0.002313938458,-0.002338160062,-0.002362348605,
  -0.002386476612,-0.002410555724, -0.00243459316,-0.002458594972,-0.002482550917,
  -0.002506444696,-0.002530272119,-0.002554023638,-0.002577699255,-0.002601315966,
  -0.002624881919,-0.002648399211,-0.002671816852, -0.00269507058,-0.002718378091,
  -0.002741512144,-0.002764584031,-0.002787564648,-0.002810447011,  -0.0028332402,
  -0.002855928149,-0.002878515515,-0.002901000669,-0.002923369175,-0.002945623826,
  -0.002967765322,-0.002989791799,-0.003011699067,-0.003033478744,-0.003055138979,
  -0.003076677676,-0.003098077141,-0.003119350877,-0.003140480723,-0.003161467612,
  -0.003182328306, -0.00320299645,-0.003223580308,-0.003243983723,-0.003264221828,
  -0.003284322331,-0.003304275684,-0.003324069548, -0.00334368716, -0.00336312619,
  -0.003382396186,-0.003401496215,-0.003420434659,-0.003439212916,-0.003457813058,
   -0.00347621832,-0.003494408913,-0.003512420459,-0.003530328628,-0.003547935514,
  -0.003565414809,-0.003582682926,-0.003599752905,-0.003616628703,-0.003633293789,
  -0.003649758874,-0.003666014643,-0.003682055278,-0.003697891254,-0.003713516984,
  -0.003728928277,-0.003744121641,-0.003759095212,-0.003773855045,-0.003788387869,
  -0.003802688094,-0.003816768061,-0.003830609843,-0.003844225081,-0.003857612843,
  -0.003870743327, -0.00388369849,-0.003896347247,-0.003908782732,-0.003920997959,
  -0.003932957072,-0.003944656812,-0.003956101369, -0.00396730518,  -0.0039782729,
  -0.003988994751,-0.003999469802,-0.004009684082,-0.004019625951,-0.004029303789,
  -0.004038729239,-0.004047927912,-0.004056874663,-0.004065479152,-0.004073911346,
  -0.004082032014,-0.004089897033,-0.004097496159,-0.004104820546,-0.004111884627,
  -0.004118673969,-0.004125195555,-0.004131454043,-0.004137438256,-0.004143147729,
  -0.004148583394,-0.004153745715,-0.004158634227,-0.004163238686,-0.004167567473,
  -0.004171626177,-0.004175401293,-0.004178907257,-0.004182133358,-0.004185074475,
  -0.004187769722,-0.004190110601,-0.004192245658, -0.00419408083,-0.004195607267,
  -0.004196857102,-0.004197839182,-0.004198555369,-0.004198990762,   0.9958008528,
  -0.004198990762,-0.004198555369,-0.004197839182,-0.004196857102,-0.004195607267,
   -0.00419408083,-0.004192245658,-0.004190110601,-0.004187769722,-0.004185074475,
  -0.004182133358,-0.004178907257,-0.004175401293,-0.004171626177,-0.004167567473,
  -0.004163238686,-0.004158634227,-0.004153745715,-0.004148583394,-0.004143147729,
  -0.004137438256,-0.004131454043,-0.004125195555,-0.004118673969,-0.004111884627,
  -0.004104820546,-0.004097496159,-0.004089897033,-0.004082032014,-0.004073911346,
  -0.004065479152,-0.004056874663,-0.004047927912,-0.004038729239,-0.004029303789,
  -0.004019625951,-0.004009684082,-0.003999469802,-0.003988994751,  -0.0039782729,
   -0.00396730518,-0.003956101369,-0.003944656812,-0.003932957072,-0.003920997959,
  -0.003908782732,-0.003896347247, -0.00388369849,-0.003870743327,-0.003857612843,
  -0.003844225081,-0.003830609843,-0.003816768061,-0.003802688094,-0.003788387869,
  -0.003773855045,-0.003759095212,-0.003744121641,-0.003728928277,-0.003713516984,
  -0.003697891254,-0.003682055278,-0.003666014643,-0.003649758874,-0.003633293789,
  -0.003616628703,-0.003599752905,-0.003582682926,-0.003565414809,-0.003547935514,
  -0.003530328628,-0.003512420459,-0.003494408913, -0.00347621832,-0.003457813058,
  -0.003439212916,-0.003420434659,-0.003401496215,-0.003382396186, -0.00336312619,
   -0.00334368716,-0.003324069548,-0.003304275684,-0.003284322331,-0.003264221828,
  -0.003243983723,-0.003223580308, -0.00320299645,-0.003182328306,-0.003161467612,
  -0.003140480723,-0.003119350877,-0.003098077141,-0.003076677676,-0.003055138979,
  -0.003033478744,-0.003011699067,-0.002989791799,-0.002967765322,-0.002945623826,
  -0.002923369175,-0.002901000669,-0.002878515515,-0.002855928149,  -0.0028332402,
  -0.002810447011,-0.002787564648,-0.002764584031,-0.002741512144,-0.002718378091,
   -0.00269507058,-0.002671816852,-0.002648399211,-0.002624881919,-0.002601315966,
  -0.002577699255,-0.002554023638,-0.002530272119,-0.002506444696,-0.002482550917,
  -0.002458594972, -0.00243459316,-0.002410555724,-0.002386476612,-0.002362348605,
  -0.002338160062,-0.002313938458,-0.002289713593,-0.002265398158,-0.002241088543,
  -0.002216739347,-0.002192367334,-0.002167982748, -0.00214357255,-0.002119156998,
  -0.002094725147,-0.002070276532,-0.002045824891,-0.002021367894,-0.001996906009,
  -0.001972442027,-0.001947981887,-0.001923536416,-0.001899098977,  -0.0018746719,
  -0.001850266941,-0.001825873507,-0.001801505336,-0.001777163125, -0.00175280741,
  -0.001728600473,-0.001704258961, -0.00168002909,-0.001655875472,-0.001631747116,
  -0.001607639366,-0.001583558042,-0.001559525728,-0.001535554416,-0.001511644921,
  -0.001487803063,-0.001464018947,-0.001440283027,-0.001416600193,-0.001392980339,
  -0.001369444653,-0.001345977886,-0.001322548836,-0.001299245632,-0.001275993767,
  -0.001252832939,-0.001229756395,-0.001206755755,-0.001183849643,-0.001161020715,
  -0.001138282823,-0.001115644118,-0.001093095983,-0.001070644823,-0.001048296108,
  -0.001026054379, -0.00100392045,-0.0009818868712,-0.0009599633049,-0.0009381537093,
  -0.000916450168,-0.0008948670002,-0.0008733960567,-0.0008520369884,-0.0008308584802,
  -0.0008096368401,-0.0007887391839,-0.0007679046248,-0.0007471441058,-0.0007265114691,
  -0.000706026738,-0.0006856988766,-0.0006655142643, -0.00064546254,-0.0006255424814,
  -0.0006057466962,-0.0005860843812,-0.0005665707286,-0.0005472105695,-0.0005280034384,
  -0.0005089304759,-0.0004900046042,-0.0004712668888,-0.0004526384873,-0.0004341829917,
  -0.0004158717929,-0.0003977099259,-0.0003797111276,-0.0003618590126,-0.0003441759327,
  -0.0003266549029,-0.0003092898114,-0.0002920928528,-0.0002750631247,-0.0002581986773,
  -0.000241496542,-0.0002249565587,-0.0002085895976,-0.0001923901582,-0.0001763556356,
  -0.0001604969875,-0.0001448033727,-0.0001292849629,-0.0001139515298,-9.869766654e-005,
  -8.384768444e-005,-6.893452519e-005,-5.423503535e-005,-3.977317829e-005,
  -2.550746467e-005,-1.141425219e-005,2.524029696e-006,1.630012048e-005,2.990307985e-005,
  4.332801109e-005,5.656020949e-005,6.959986786e-005,8.24578965e-005,9.514023986e-005,
  0.0001076502158,0.0001199680628,0.0001320999727,0.0001440910564,0.0001558690274,
   0.000167484337,0.0001789129747,0.0001901533542,0.0002012184268,0.0002120876306,
  0.0002227817895,0.0002332955482,0.0002436202049,0.0002537668624,0.0002637364087,
  0.0002735276357,0.0002831367601,0.0002925609297,0.0003018105926,0.0003108813253,
  0.0003197686165, 0.000328482769,0.0003370129853,0.0003453680838, 0.000353568641,
  0.0003614437592,0.0003694657644,0.0003770334297,0.0003844274033,0.0003917048161,
  0.0003988420067,0.0004058167688,0.0004126035783,0.0004191997577,0.0004256106913,
  0.0004318390274,0.0004379020247,0.0004438071337, 0.000449549465,0.0004551245656,
  0.0004605264985,0.0004657746176,0.0004708688939,0.0004757604038,0.0004805121862,
   0.000485082448,  0.00048948935,0.0004937388003,0.0004978174111,0.0005017499789,
   0.000505518401,0.0005091274506,0.0005125894677,0.0005158963031, 0.000519046851,
  0.0005220419844,0.0005248864181,0.0005275860312,0.0005301316851,0.0005325271632,
  0.0005347791594,0.0005368787097,0.0005388373393,0.0005406484706,0.0005422724062,
  0.0005439945962,0.0005451107863, 0.000546403171,0.0005476014921,0.0005486205337,
  0.0005494623911,0.0005501415581,0.0005506875459,0.0005511139752,0.0005514255608,
  0.0005516292294,0.0005517128739,0.0005516676465,0.0005514948862,0.0005511977361,
  0.0005507848109,0.0005502384738,0.0005495533114,0.0005487813032,0.0005478708772,
  0.0005468601594, 0.000545740535,0.0005445074057,  0.00054317998,0.0005417348002,
  0.0005401912495,0.0005385497934,0.0005367987906,0.0005349462153,0.0005329960841,
  0.0005309511907,0.0005288097891,0.0005265666405,0.0005242325133,0.0005218077567,
  0.0005192880053,0.0005166847259, 0.000513989944,0.0005112125655,0.0005084362347,
  0.0005051696789,0.0005025088903,0.0004994241172,0.0004961660597,0.0004928449634,
   0.000489487662,0.0004861006455, 0.000482664298,0.0004791654064,0.0004755957925,
  0.0004719423305,0.0004682115105,0.0004644128785,0.0004605494323, 0.000456623151,
  0.0004526277189,0.0004485841782,0.0004445101076,0.0004403601924,0.0004361833853,
  0.0004319518921,0.0004276727559,0.0004233553773,0.0004189797328,0.0004145727144,
  0.0004101183731, 0.000405615312,0.0004010783159,0.0003965043579,0.0003918921866,
  0.0003872405214,0.0003825530584,0.0003778397804,0.0003730947501,0.0003683195391,
  0.0003635227913,0.0003586970561, 0.000353853422,0.0003489877854,0.0003439303255,
  0.0003396002576,0.0003342042619,0.0003291572793,0.0003242500243,0.0003193668963,
  0.0003144615621,0.0003095078864,0.0003045119811,0.0002994825772,0.0002944288717,
  0.0002893716155,0.0002843158727,0.0002792609448,0.0002742099168,0.0002691658156,
  0.0002641422034, 0.000259124994,0.0002540934656,0.0002490914776,0.0002440771932,
  0.0002390730951,0.0002340767096,0.0002290774428,0.0002240998874,0.0002191184321,
  0.0002141495497,0.0002092007344,0.0002042604028,0.0001993324258,0.0001944209944,
  0.0001895318564,0.0001846665255,0.0001798173907,0.0001749921503,0.0001701934234,
   0.000165415142,0.0001606668375,0.0001559399243,0.0001512390299,0.0001469656272,
  0.0001412085257, 0.000137211071,0.0001328812941,0.0001283756137,0.0001238006662,
   0.000119214099,0.0001146621289,0.0001101603411,0.0001057175396,0.0001013387009,
  9.701083764e-005,9.272975149e-005,8.849598089e-005,8.430644084e-005,8.01578135e-005,
  7.603244012e-005,7.193769852e-005,6.789666804e-005,6.386849418e-005,5.988968769e-005,
  5.594453978e-005,5.203453111e-005,4.817563968e-005,4.434338189e-005,4.05668543e-005,
  3.683530304e-005,3.314111018e-005,2.949771624e-005,2.590603435e-005,2.236529508e-005,
  1.887112376e-005,1.542166137e-005,1.202601834e-005,8.678948689e-006,5.377413345e-006,
  2.127746711e-006,-1.079116373e-006,-4.234968401e-006,-7.342594472e-006,
  -1.157638235e-005,-1.20257173e-005,-1.580026947e-005,-1.921071453e-005,
  -2.23471834e-005,-2.528377627e-005,-2.806592238e-005,-3.07409282e-005,-3.333387212e-005,
  -3.58653997e-005,-3.835477037e-005,-4.080127837e-005,-4.320771404e-005,
  -4.557999637e-005,-4.791995889e-005,-5.022837286e-005,-5.248687012e-005,
  -5.469620373e-005,-5.687864541e-005,-5.899376265e-005,-6.106881483e-005,
  -6.308902812e-005,-6.504964404e-005,-6.696646597e-005,-6.880980072e-005,
  -7.060628559e-005,-7.2346651e-005,-7.401945186e-005,-7.563558029e-005,-7.719746645e-005,
  -7.870612171e-005,-8.015791536e-005,-8.154998795e-005,-8.289227117e-005,
  -8.418226207e-005,-8.541729039e-005,-8.66043556e-005,-8.773519949e-005,
  -8.881753456e-005,-8.985015302e-005,-8.491730114e-005,-9.529728413e-005,
  -9.514101839e-005,-9.514296835e-005,-9.52753544e-005,-9.550793038e-005,
  -9.582591156e-005,-9.620213677e-005,-9.66219377e-005,-9.706959827e-005,
  -9.752402548e-005,-9.798025712e-005,-9.843080625e-005,-9.886387852e-005,
  -9.926950588e-005,-9.963668708e-005,-9.997537563e-005,-0.0001002827194,
  -0.0001005304002,-0.0001007492683,-0.0001009135958,-0.0001010308843,-0.000101105994,
  -0.0001011188142,-0.0001010997221,-0.0001010232372,-0.0001008952386,-0.0001007298197,
  -0.0001005200756,-0.0001002643403,-9.996187146e-005,-9.96174349e-005,-9.923732432e-005,
  -9.881438746e-005,-9.835133096e-005,-9.785284055e-005,-9.731399041e-005,
  -9.674464673e-005,-9.614052397e-005,-9.550420509e-005,  -0.0065831705
};

vu32 FirHighPassTmpIRBuffer[FIR_HIGHPASS_ORDER];//临时存放fir之前的原始数据，每到一个处理一次
vu8 FirHighPassTmpIRInIdx=0;

u8 AddHighPassIRData(u32 data)
{
	static vu16 Idx=SAMPLE_TIMER_SECOND*AFE4490_SAMPLE_RATE;//0;
	u32 val=0;
	u16 tmpidx=0;
	//val=data;
	if(FirHighPassTmpIRInIdx==FIR_HIGHPASS_ORDER)
	{
		memmove((void*)FirHighPassTmpIRBuffer,(void*)&FirHighPassTmpIRBuffer[1],sizeof(FirHighPassTmpIRBuffer)-sizeof(vu32));
		FirHighPassTmpIRBuffer[FIR_HIGHPASS_ORDER-1]=data;
		val=GetFilterData((u32*)FirHighPassTmpIRBuffer,FirCoff,FIR_HIGHPASS_ORDER);
	}
	else
	{
		FirHighPassTmpIRBuffer[FirHighPassTmpIRInIdx]=data;
		FirHighPassTmpIRInIdx++;
	}
	return val;
}

//u32 GetFilterData(const u32* in, float* b,u16 order);