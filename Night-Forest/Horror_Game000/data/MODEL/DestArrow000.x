xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 127;
 19.44521;3.71050;0.00000;,
 20.77929;9.11103;0.00000;,
 9.71567;8.52164;-12.93102;,
 8.77231;5.30081;-11.98766;,
 40.99449;10.44515;0.00000;,
 28.98749;8.26544;-28.98749;,
 44.21532;6.93133;0.00000;,
 31.26495;6.93133;-31.26495;,
 45.54944;3.71050;0.00000;,
 32.20831;3.71050;-32.20831;,
 44.21532;0.48967;0.00000;,
 31.26495;0.48967;-31.26495;,
 40.99449;-0.84445;-0.00000;,
 28.98749;-0.84445;-28.98749;,
 20.77929;0.48967;0.00000;,
 9.71567;0.48967;-12.93102;,
 19.44521;3.71050;0.00000;,
 8.77231;5.30081;-11.98766;,
 -0.00000;8.52164;-37.77364;,
 -0.00000;5.30081;-22.66056;,
 -0.00000;8.26544;-40.99449;,
 -0.00000;6.93133;-44.21532;,
 -0.00000;3.71050;-45.54944;,
 -0.00000;0.48967;-44.21532;,
 -0.00000;-0.84445;-40.99449;,
 -0.00000;0.48967;-23.99465;,
 -0.00000;5.30081;-22.66056;,
 -9.63667;6.93133;-12.93102;,
 -8.69331;3.71050;-11.98766;,
 -28.98749;8.26544;-28.98749;,
 -31.26495;6.93133;-31.26495;,
 -32.20831;3.71050;-32.20831;,
 -31.26495;0.48967;-31.26495;,
 -28.98749;-0.84445;-28.98749;,
 -9.63667;0.48967;-12.93102;,
 -8.69331;3.71050;-11.98766;,
 -20.70029;6.93133;0.00000;,
 -19.36621;3.71050;0.00000;,
 -40.99449;8.26544;0.00000;,
 -44.21532;6.93133;0.00000;,
 -45.54944;3.71050;0.00000;,
 -44.21532;0.48967;0.00000;,
 -40.99449;-0.84445;0.00000;,
 -20.70029;0.48967;0.00000;,
 -19.36621;3.71050;0.00000;,
 -9.63667;6.93133;12.13964;,
 -8.69330;3.71050;11.19627;,
 -28.98746;8.26544;28.98749;,
 -31.26494;6.93133;31.26496;,
 -32.20830;3.71050;32.20832;,
 -31.26494;0.48967;31.26496;,
 -28.98746;-0.84445;28.98749;,
 -9.63667;0.48967;12.13964;,
 -8.69330;3.71050;11.19627;,
 0.00000;6.93133;23.20325;,
 0.00000;3.71050;21.86916;,
 0.00000;8.26544;40.99449;,
 0.00000;6.93133;44.21532;,
 0.00000;3.71050;45.54944;,
 0.00000;0.48967;44.21532;,
 0.00000;-0.84445;40.99449;,
 0.00000;0.48967;23.20325;,
 0.00000;3.71050;21.86916;,
 26.71001;9.11103;26.71002;,
 8.77231;3.71050;11.19627;,
 28.98747;10.44515;28.98749;,
 31.26495;6.93133;31.26495;,
 32.20831;3.71050;32.20831;,
 31.26495;0.48967;31.26495;,
 28.98747;-0.84445;28.98749;,
 26.71001;0.48967;26.71002;,
 8.77231;3.71050;11.19627;,
 20.77929;9.11103;0.00000;,
 19.44521;3.71050;0.00000;,
 40.99449;10.44515;0.00000;,
 44.21532;6.93133;0.00000;,
 45.54944;3.71050;0.00000;,
 44.21532;0.48967;0.00000;,
 40.99449;-0.84445;-0.00000;,
 20.77929;0.48967;0.00000;,
 19.44521;3.71050;0.00000;,
 -7.88396;7.47890;-56.76822;,
 7.47030;7.47890;-56.76822;,
 7.47030;1.00002;-56.76822;,
 -7.88396;1.00002;-56.76822;,
 7.47030;7.47890;-56.76822;,
 7.47030;7.47890;-33.38734;,
 7.47030;1.00002;-33.38734;,
 7.47030;1.00002;-56.76822;,
 7.47030;7.47890;-33.38734;,
 -7.88396;7.47890;-33.38734;,
 -7.88396;1.00002;-33.38734;,
 7.47030;1.00002;-33.38734;,
 -7.88396;7.47890;-33.38734;,
 -7.88396;7.47890;-56.76822;,
 -7.88396;1.00002;-56.76822;,
 -7.88396;1.00002;-33.38734;,
 7.47030;7.47890;-56.76822;,
 -7.88396;7.47890;-56.76822;,
 -7.88396;1.00002;-56.76822;,
 7.47030;1.00002;-56.76822;,
 -0.88404;0.02565;-57.45942;,
 -0.78904;4.24427;-87.93980;,
 10.40813;0.95613;-57.75492;,
 -0.78904;4.24427;-87.93980;,
 15.82325;3.64931;-57.58535;,
 -0.78904;4.24427;-87.93980;,
 12.18920;6.52753;-57.04995;,
 -0.78904;4.24427;-87.93980;,
 1.63479;7.90481;-56.46243;,
 -0.78904;4.24427;-87.93980;,
 -9.65738;6.97431;-56.16688;,
 -0.78904;4.24427;-87.93980;,
 -15.07250;4.28114;-56.33649;,
 -0.78904;4.24427;-87.93980;,
 -11.43846;1.40291;-56.87186;,
 -0.78904;4.24427;-87.93980;,
 -0.88404;0.02565;-57.45942;,
 0.37537;3.96522;-56.96091;,
 -0.88404;0.02565;-57.45942;,
 10.40813;0.95613;-57.75492;,
 15.82325;3.64931;-57.58535;,
 12.18920;6.52753;-57.04995;,
 1.63479;7.90481;-56.46243;,
 -9.65738;6.97431;-56.16688;,
 -15.07250;4.28114;-56.33649;,
 -11.43846;1.40291;-56.87186;;
 
 86;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;3,2,18,19;,
 4;2,5,20,18;,
 4;5,7,21,20;,
 4;7,9,22,21;,
 4;9,11,23,22;,
 4;11,13,24,23;,
 4;13,15,25,24;,
 4;15,17,26,25;,
 4;19,18,27,28;,
 4;18,20,29,27;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;25,26,35,34;,
 4;28,27,36,37;,
 4;27,29,38,36;,
 4;29,30,39,38;,
 4;30,31,40,39;,
 4;31,32,41,40;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 4;34,35,44,43;,
 4;37,36,45,46;,
 4;36,38,47,45;,
 4;38,39,48,47;,
 4;39,40,49,48;,
 4;40,41,50,49;,
 4;41,42,51,50;,
 4;42,43,52,51;,
 4;43,44,53,52;,
 4;46,45,54,55;,
 4;45,47,56,54;,
 4;47,48,57,56;,
 4;48,49,58,57;,
 4;49,50,59,58;,
 4;50,51,60,59;,
 4;51,52,61,60;,
 4;52,53,62,61;,
 4;55,54,63,64;,
 4;54,56,65,63;,
 4;56,57,66,65;,
 4;57,58,67,66;,
 4;58,59,68,67;,
 4;59,60,69,68;,
 4;60,61,70,69;,
 4;61,62,71,70;,
 4;64,63,72,73;,
 4;63,65,74,72;,
 4;65,66,75,74;,
 4;66,67,76,75;,
 4;67,68,77,76;,
 4;68,69,78,77;,
 4;69,70,79,78;,
 4;70,71,80,79;,
 4;81,82,83,84;,
 4;85,86,87,88;,
 4;89,90,91,92;,
 4;93,94,95,96;,
 4;93,86,97,98;,
 4;99,100,87,96;,
 3;101,102,103;,
 3;103,104,105;,
 3;105,106,107;,
 3;107,108,109;,
 3;109,110,111;,
 3;111,112,113;,
 3;113,114,115;,
 3;115,116,117;,
 3;118,119,120;,
 3;118,120,121;,
 3;118,121,122;,
 3;118,122,123;,
 3;118,123,124;,
 3;118,124,125;,
 3;118,125,126;,
 3;118,126,119;;
 
 MeshMaterialList {
  3;
  86;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  2,
  2,
  2,
  2,
  2,
  2,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.000000;0.633726;0.109804;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.743529;0.009412;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  113;
  -0.752573;0.001258;0.658508;,
  -0.711675;0.285718;0.641782;,
  0.278614;0.960181;-0.020640;,
  0.810210;0.586042;0.010688;,
  1.000000;0.000000;0.000000;,
  0.698872;-0.715247;-0.000000;,
  0.124745;-0.992130;-0.010795;,
  -0.299035;-0.954211;0.007679;,
  -0.768314;0.120089;0.628707;,
  -0.687925;0.485633;0.539371;,
  0.179541;0.966039;-0.185832;,
  0.534374;0.671671;-0.513131;,
  0.707107;0.000000;-0.707107;,
  0.494177;-0.715247;-0.494177;,
  0.114978;-0.986640;-0.115423;,
  -0.044636;-0.998044;0.043776;,
  -0.772146;0.246264;0.585786;,
  -0.016295;0.972602;0.231905;,
  0.002808;0.978653;-0.205502;,
  -0.000000;0.715247;-0.698872;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;-0.715247;-0.698872;,
  0.000006;-0.986140;-0.165913;,
  0.000011;-0.998396;0.056615;,
  0.736727;0.261156;0.623724;,
  0.376676;0.872718;0.310611;,
  -0.126561;0.983278;-0.130943;,
  -0.494177;0.715247;-0.494177;,
  -0.707107;0.000000;-0.707107;,
  -0.494177;-0.715247;-0.494177;,
  -0.115016;-0.986629;-0.115477;,
  0.044559;-0.998052;0.043667;,
  0.753498;0.000000;0.657450;,
  0.708196;0.341513;0.617922;,
  -0.167948;0.985796;-0.000070;,
  -0.698872;0.715247;-0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.698872;-0.715247;-0.000000;,
  -0.167948;-0.985796;-0.000070;,
  0.052479;-0.998622;-0.000135;,
  0.748388;0.000000;-0.663261;,
  0.706374;0.330346;-0.626025;,
  -0.115528;0.986516;0.115925;,
  -0.494177;0.715247;0.494177;,
  -0.707107;0.000000;0.707107;,
  -0.494177;-0.715247;0.494177;,
  -0.115528;-0.986516;0.115925;,
  0.043530;-0.998137;-0.042761;,
  0.764580;0.000000;-0.644528;,
  0.207652;0.805515;-0.555001;,
  -0.013762;0.982926;0.183485;,
  0.015021;0.671671;0.740697;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.715247;0.698872;,
  -0.010332;-0.992312;0.123333;,
  -0.010251;-0.953690;-0.300615;,
  -0.365533;0.772688;-0.518979;,
  -0.279917;0.900324;-0.333261;,
  0.158083;0.973109;0.167536;,
  0.580463;0.586042;0.565347;,
  0.707107;0.000000;0.707107;,
  0.494177;-0.715247;0.494177;,
  0.061949;-0.996187;0.061432;,
  -0.234744;-0.946640;-0.220836;,
  -0.320553;0.932133;-0.168446;,
  -0.009334;0.999113;-0.041068;,
  -0.731105;-0.283307;0.620663;,
  -0.737273;-0.253403;0.626271;,
  -0.742730;-0.223255;0.631275;,
  0.561800;0.701233;0.438922;,
  0.747715;-0.280846;0.601704;,
  0.728457;-0.311394;0.610233;,
  0.052479;0.998622;-0.000135;,
  0.708196;-0.341513;0.617922;,
  0.731640;0.000000;-0.681692;,
  0.688563;0.338065;-0.641555;,
  0.043530;0.998137;-0.042761;,
  0.688563;-0.338065;-0.641555;,
  0.706374;-0.330346;-0.626025;,
  0.035065;0.997901;-0.054435;,
  0.723749;-0.322422;-0.610108;,
  -0.047494;0.786661;-0.615556;,
  0.009667;-0.807100;-0.590336;,
  -0.324112;-0.899210;-0.293893;,
  -0.643118;0.673201;-0.364966;,
  -0.590550;-0.804490;0.063613;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.029084;-0.990126;-0.137129;,
  0.262617;-0.943894;-0.200240;,
  0.436886;-0.862319;-0.256000;,
  0.356295;0.908856;-0.216875;,
  0.018677;0.992967;-0.116911;,
  -0.262745;0.952307;-0.155162;,
  -0.431727;0.880418;-0.196151;,
  -0.394372;-0.892998;-0.216852;,
  -0.066088;-0.973079;-0.220793;,
  0.037206;-0.137145;0.989852;,
  0.566216;0.769739;-0.294790;,
  0.046378;0.979608;-0.195495;,
  -0.621062;-0.732100;-0.279842;,
  0.037206;-0.137151;0.989851;,
  0.037206;-0.137144;0.989852;,
  0.037207;-0.137144;0.989852;,
  0.037206;-0.137145;0.989852;,
  0.037207;-0.137141;0.989853;,
  0.037207;-0.137145;0.989852;,
  0.037206;-0.137144;0.989852;,
  0.037207;-0.137146;0.989852;;
  86;
  4;0,1,9,8;,
  4;64,2,10,65;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;66,0,8,67;,
  4;8,9,17,16;,
  4;65,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;67,8,16,68;,
  4;69,17,25,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;70,70,70,71;,
  4;24,25,33,32;,
  4;25,26,34,72;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;71,24,32,73;,
  4;74,75,41,40;,
  4;72,34,42,76;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;77,74,40,78;,
  4;40,41,49,48;,
  4;76,42,50,79;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;78,40,48,80;,
  4;81,49,57,56;,
  4;49,50,58,57;,
  4;50,51,59,58;,
  4;51,52,60,59;,
  4;52,53,61,60;,
  4;53,54,62,61;,
  4;54,55,63,62;,
  4;55,82,83,63;,
  4;56,57,64,84;,
  4;57,58,2,64;,
  4;58,59,3,2;,
  4;59,60,4,3;,
  4;60,61,5,4;,
  4;61,62,6,5;,
  4;62,63,7,6;,
  4;63,83,85,7;,
  4;86,86,86,86;,
  4;87,87,87,87;,
  4;88,88,88,88;,
  4;89,89,89,89;,
  4;90,90,90,90;,
  4;91,91,91,91;,
  3;92,100,93;,
  3;93,100,94;,
  3;102,103,95;,
  3;95,103,96;,
  3;96,103,97;,
  3;97,103,98;,
  3;104,100,99;,
  3;99,100,92;,
  3;101,105,106;,
  3;101,106,107;,
  3;101,107,108;,
  3;101,108,109;,
  3;101,109,110;,
  3;101,110,111;,
  3;101,111,112;,
  3;101,112,105;;
 }
 MeshTextureCoords {
  127;
  0.000000;0.000000;,
  0.000000;0.125000;,
  0.125000;0.125000;,
  0.125000;0.000000;,
  0.000000;0.250000;,
  0.125000;0.250000;,
  0.000000;0.375000;,
  0.125000;0.375000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.000000;0.625000;,
  0.125000;0.625000;,
  0.000000;0.750000;,
  0.125000;0.750000;,
  0.000000;0.875000;,
  0.125000;0.875000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.250000;0.125000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.250000;0.375000;,
  0.250000;0.500000;,
  0.250000;0.625000;,
  0.250000;0.750000;,
  0.250000;0.875000;,
  0.250000;1.000000;,
  0.375000;0.125000;,
  0.375000;0.000000;,
  0.375000;0.250000;,
  0.375000;0.375000;,
  0.375000;0.500000;,
  0.375000;0.625000;,
  0.375000;0.750000;,
  0.375000;0.875000;,
  0.375000;1.000000;,
  0.500000;0.125000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.500000;0.375000;,
  0.500000;0.500000;,
  0.500000;0.625000;,
  0.500000;0.750000;,
  0.500000;0.875000;,
  0.500000;1.000000;,
  0.625000;0.125000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.625000;0.375000;,
  0.625000;0.500000;,
  0.625000;0.625000;,
  0.625000;0.750000;,
  0.625000;0.875000;,
  0.625000;1.000000;,
  0.750000;0.125000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  0.750000;0.375000;,
  0.750000;0.500000;,
  0.750000;0.625000;,
  0.750000;0.750000;,
  0.750000;0.875000;,
  0.750000;1.000000;,
  0.875000;0.125000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.875000;0.375000;,
  0.875000;0.500000;,
  0.875000;0.625000;,
  0.875000;0.750000;,
  0.875000;0.875000;,
  0.875000;1.000000;,
  1.000000;0.125000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  1.000000;0.375000;,
  1.000000;0.500000;,
  1.000000;0.625000;,
  1.000000;0.750000;,
  1.000000;0.875000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}