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
 160;
 0.24435;51.21230;2.37561;,
 7.29466;49.22900;-4.67470;,
 0.24435;49.22900;-7.59502;,
 0.24435;51.21230;2.37561;,
 10.21498;49.22900;2.37561;,
 0.24435;51.21230;2.37561;,
 7.29466;49.22900;9.42593;,
 0.24435;51.21230;2.37561;,
 0.24435;49.22900;12.34624;,
 0.24435;51.21230;2.37561;,
 -6.80597;49.22900;9.42593;,
 0.24435;51.21230;2.37561;,
 -9.72629;49.22900;2.37561;,
 0.24435;51.21230;2.37561;,
 -6.80597;49.22900;-4.67470;,
 0.24435;51.21230;2.37561;,
 0.24435;49.22900;-7.59502;,
 13.27163;43.58110;-10.65167;,
 0.24435;43.58110;-16.04775;,
 18.66772;43.58110;2.37561;,
 13.27163;43.58110;15.40290;,
 0.24435;43.58110;20.79897;,
 -12.78294;43.58110;15.40290;,
 -18.17901;43.58110;2.37561;,
 -12.78294;43.58110;-10.65167;,
 0.24435;43.58110;-16.04775;,
 17.26532;35.12838;-14.64535;,
 0.24435;35.12838;-21.69566;,
 24.31562;35.12838;2.37561;,
 17.26532;35.12838;19.39659;,
 0.24435;35.12838;26.44691;,
 -16.77663;35.12838;19.39656;,
 -23.82692;35.12838;2.37561;,
 -16.77663;35.12838;-14.64535;,
 0.24435;35.12838;-21.69566;,
 18.66772;25.15774;-16.04775;,
 0.24435;25.15774;-23.67895;,
 26.29891;25.15774;2.37561;,
 18.66772;25.15774;20.79897;,
 0.24435;25.15774;28.43017;,
 -18.17901;25.15774;20.79897;,
 -25.81021;25.15774;2.37561;,
 -18.17901;25.15774;-16.04775;,
 0.24435;25.15774;-23.67895;,
 17.26532;15.18707;-14.64535;,
 0.24435;15.18707;-21.69566;,
 24.31562;15.18707;2.37561;,
 17.26532;15.18707;19.39659;,
 0.24435;15.18707;26.44691;,
 -16.77663;15.18707;19.39656;,
 -23.82692;15.18707;2.37561;,
 -16.77663;15.18707;-14.64535;,
 0.24435;15.18707;-21.69566;,
 13.27163;6.73438;-10.65167;,
 0.24435;6.73438;-16.04775;,
 18.66772;6.73438;2.37561;,
 13.27163;6.73438;15.40290;,
 0.24435;6.73438;20.79897;,
 -12.78294;6.73438;15.40290;,
 -18.17901;6.73438;2.37561;,
 -12.78294;6.73438;-10.65167;,
 0.24435;6.73438;-16.04775;,
 7.29466;1.08647;-4.67470;,
 0.24435;1.08647;-7.59502;,
 10.21498;1.08647;2.37561;,
 7.29466;1.08647;9.42593;,
 0.24435;1.08647;12.34624;,
 -6.80597;1.08647;9.42593;,
 -9.72629;1.08647;2.37561;,
 -6.80597;1.08647;-4.67470;,
 0.24435;1.08647;-7.59502;,
 0.24435;-0.89683;2.37561;,
 0.24435;-0.89683;2.37561;,
 0.24435;-0.89683;2.37561;,
 0.24435;-0.89683;2.37561;,
 0.24435;-0.89683;2.37561;,
 0.24435;-0.89683;2.37561;,
 0.24435;-0.89683;2.37561;,
 0.24435;-0.89683;2.37561;,
 25.03527;22.25787;2.37561;,
 25.93956;24.44103;2.37561;,
 18.44031;24.44103;-15.72916;,
 17.80088;22.25787;-15.08972;,
 28.12273;25.34534;2.37561;,
 19.98404;25.34534;-17.27289;,
 30.30588;24.44103;2.37561;,
 21.52778;24.44103;-18.81663;,
 31.21019;22.25787;2.37561;,
 22.16724;22.25787;-19.45608;,
 30.30588;20.07470;2.37561;,
 21.52778;20.07470;-18.81663;,
 28.12273;19.17041;2.37561;,
 19.98404;19.17041;-17.27289;,
 25.93956;20.07470;2.37561;,
 18.44031;20.07470;-15.72916;,
 25.03527;22.25787;2.37561;,
 17.80088;22.25787;-15.08972;,
 0.33554;24.44103;-23.22841;,
 0.33554;22.25787;-22.32410;,
 0.33554;25.34534;-25.41159;,
 0.33554;24.44103;-27.59472;,
 0.33554;22.25787;-28.49904;,
 0.33554;20.07470;-27.59472;,
 0.33554;19.17041;-25.41159;,
 0.33554;20.07470;-23.22841;,
 0.33554;22.25787;-22.32410;,
 -17.76924;24.44103;-15.72916;,
 -17.12980;22.25787;-15.08972;,
 -19.31296;25.34534;-17.27289;,
 -20.85670;24.44103;-18.81663;,
 -21.49615;22.25787;-19.45608;,
 -20.85670;20.07470;-18.81663;,
 -19.31296;19.17041;-17.27289;,
 -17.76924;20.07470;-15.72916;,
 -17.12980;22.25787;-15.08972;,
 -25.26849;24.44103;2.37561;,
 -24.36419;22.25787;2.37561;,
 -27.45166;25.34534;2.37561;,
 -29.63481;24.44103;2.37561;,
 -30.53912;22.25787;2.37561;,
 -29.63481;20.07470;2.37561;,
 -27.45166;19.17041;2.37561;,
 -25.26849;20.07470;2.37561;,
 -24.36419;22.25787;2.37561;,
 -17.76924;24.44103;20.48041;,
 -17.12980;22.25787;19.84096;,
 -19.31296;25.34534;22.02412;,
 -20.85670;24.44103;23.56785;,
 -21.49613;22.25787;24.20732;,
 -20.85670;20.07470;23.56785;,
 -19.31296;19.17041;22.02412;,
 -17.76924;20.07470;20.48041;,
 -17.12980;22.25787;19.84096;,
 0.33554;24.44103;27.97964;,
 0.33554;22.25787;27.07534;,
 0.33554;25.34534;30.16281;,
 0.33554;24.44103;32.34597;,
 0.33554;22.25787;33.25028;,
 0.33554;20.07470;32.34597;,
 0.33554;19.17041;30.16281;,
 0.33554;20.07470;27.97964;,
 0.33554;22.25787;27.07534;,
 18.44031;24.44103;20.48041;,
 17.80088;22.25787;19.84096;,
 19.98404;25.34534;22.02412;,
 21.52778;24.44103;23.56785;,
 22.16720;22.25787;24.20732;,
 21.52778;20.07470;23.56785;,
 19.98404;19.17041;22.02412;,
 18.44031;20.07470;20.48041;,
 17.80088;22.25787;19.84096;,
 25.93956;24.44103;2.37561;,
 25.03527;22.25787;2.37561;,
 28.12273;25.34534;2.37561;,
 30.30588;24.44103;2.37561;,
 31.21019;22.25787;2.37561;,
 30.30588;20.07470;2.37561;,
 28.12273;19.17041;2.37561;,
 25.93956;20.07470;2.37561;,
 25.03527;22.25787;2.37561;;
 
 128;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 4;2,1,17,18;,
 4;1,4,19,17;,
 4;4,6,20,19;,
 4;6,8,21,20;,
 4;8,10,22,21;,
 4;10,12,23,22;,
 4;12,14,24,23;,
 4;14,16,25,24;,
 4;18,17,26,27;,
 4;17,19,28,26;,
 4;19,20,29,28;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;27,26,35,36;,
 4;26,28,37,35;,
 4;28,29,38,37;,
 4;29,30,39,38;,
 4;30,31,40,39;,
 4;31,32,41,40;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 4;36,35,44,45;,
 4;35,37,46,44;,
 4;37,38,47,46;,
 4;38,39,48,47;,
 4;39,40,49,48;,
 4;40,41,50,49;,
 4;41,42,51,50;,
 4;42,43,52,51;,
 4;45,44,53,54;,
 4;44,46,55,53;,
 4;46,47,56,55;,
 4;47,48,57,56;,
 4;48,49,58,57;,
 4;49,50,59,58;,
 4;50,51,60,59;,
 4;51,52,61,60;,
 4;54,53,62,63;,
 4;53,55,64,62;,
 4;55,56,65,64;,
 4;56,57,66,65;,
 4;57,58,67,66;,
 4;58,59,68,67;,
 4;59,60,69,68;,
 4;60,61,70,69;,
 3;63,62,71;,
 3;62,64,72;,
 3;64,65,73;,
 3;65,66,74;,
 3;66,67,75;,
 3;67,68,76;,
 3;68,69,77;,
 3;69,70,78;,
 4;79,80,81,82;,
 4;80,83,84,81;,
 4;83,85,86,84;,
 4;85,87,88,86;,
 4;87,89,90,88;,
 4;89,91,92,90;,
 4;91,93,94,92;,
 4;93,95,96,94;,
 4;82,81,97,98;,
 4;81,84,99,97;,
 4;84,86,100,99;,
 4;86,88,101,100;,
 4;88,90,102,101;,
 4;90,92,103,102;,
 4;92,94,104,103;,
 4;94,96,105,104;,
 4;98,97,106,107;,
 4;97,99,108,106;,
 4;99,100,109,108;,
 4;100,101,110,109;,
 4;101,102,111,110;,
 4;102,103,112,111;,
 4;103,104,113,112;,
 4;104,105,114,113;,
 4;107,106,115,116;,
 4;106,108,117,115;,
 4;108,109,118,117;,
 4;109,110,119,118;,
 4;110,111,120,119;,
 4;111,112,121,120;,
 4;112,113,122,121;,
 4;113,114,123,122;,
 4;116,115,124,125;,
 4;115,117,126,124;,
 4;117,118,127,126;,
 4;118,119,128,127;,
 4;119,120,129,128;,
 4;120,121,130,129;,
 4;121,122,131,130;,
 4;122,123,132,131;,
 4;125,124,133,134;,
 4;124,126,135,133;,
 4;126,127,136,135;,
 4;127,128,137,136;,
 4;128,129,138,137;,
 4;129,130,139,138;,
 4;130,131,140,139;,
 4;131,132,141,140;,
 4;134,133,142,143;,
 4;133,135,144,142;,
 4;135,136,145,144;,
 4;136,137,146,145;,
 4;137,138,147,146;,
 4;138,139,148,147;,
 4;139,140,149,148;,
 4;140,141,150,149;,
 4;143,142,151,152;,
 4;142,144,153,151;,
 4;144,145,154,153;,
 4;145,146,155,154;,
 4;146,147,156,155;,
 4;147,148,157,156;,
 4;148,149,158,157;,
 4;149,150,159,158;;
 
 MeshMaterialList {
  4;
  128;
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
  1,
  0,
  1,
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
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3;;
  Material {
   0.000000;0.432800;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.047200;0.000000;1.000000;;
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
  122;
  0.000000;1.000000;-0.000000;,
  0.000000;0.924735;-0.380611;,
  0.269132;0.924736;-0.269132;,
  0.380610;0.924735;-0.000000;,
  0.269132;0.924736;0.269132;,
  0.000000;0.924735;0.380611;,
  -0.269132;0.924736;0.269132;,
  -0.380611;0.924735;-0.000000;,
  -0.269132;0.924735;-0.269132;,
  0.000000;0.709231;-0.704976;,
  0.498493;0.709231;-0.498494;,
  0.704976;0.709231;-0.000000;,
  0.498493;0.709231;0.498493;,
  -0.000000;0.709231;0.704976;,
  -0.498494;0.709231;0.498493;,
  -0.704977;0.709231;-0.000000;,
  -0.498494;0.709231;-0.498493;,
  0.000000;0.384551;-0.923104;,
  0.652733;0.384551;-0.652733;,
  0.923104;0.384551;-0.000000;,
  0.652733;0.384551;0.652733;,
  -0.000000;0.384550;0.923104;,
  -0.652733;0.384550;0.652733;,
  -0.923104;0.384550;0.000000;,
  -0.652733;0.384551;-0.652733;,
  -0.000000;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;-0.000000;,
  0.707107;0.000000;0.707107;,
  -0.000000;0.000000;1.000000;,
  -0.707107;0.000000;0.707106;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.000000;-0.707107;,
  0.000000;-0.384551;-0.923104;,
  0.652733;-0.384551;-0.652733;,
  0.923104;-0.384551;-0.000000;,
  0.652733;-0.384551;0.652733;,
  -0.000000;-0.384551;0.923104;,
  -0.652733;-0.384551;0.652733;,
  -0.923104;-0.384551;0.000000;,
  -0.652733;-0.384551;-0.652733;,
  0.000000;-0.709231;-0.704976;,
  0.498493;-0.709231;-0.498493;,
  0.704976;-0.709231;-0.000000;,
  0.498493;-0.709232;0.498493;,
  -0.000000;-0.709231;0.704976;,
  -0.498493;-0.709231;0.498493;,
  -0.704976;-0.709231;-0.000000;,
  -0.498493;-0.709231;-0.498493;,
  0.000000;-0.924735;-0.380611;,
  0.269132;-0.924735;-0.269133;,
  0.380611;-0.924735;-0.000000;,
  0.269132;-0.924735;0.269132;,
  0.000000;-0.924735;0.380611;,
  -0.269132;-0.924735;0.269132;,
  -0.380611;-0.924735;-0.000000;,
  -0.269132;-0.924735;-0.269132;,
  0.000000;-1.000000;-0.000000;,
  -1.000000;0.000001;0.000000;,
  -0.698874;0.715245;0.000000;,
  0.000000;1.000000;-0.000000;,
  0.698872;0.715247;0.000000;,
  1.000000;0.000001;0.000001;,
  0.698869;-0.715249;0.000000;,
  0.000000;-1.000000;0.000000;,
  -0.698872;-0.715247;0.000000;,
  -0.707107;0.000001;0.707107;,
  -0.494178;0.715246;0.494178;,
  0.000000;1.000000;-0.000001;,
  0.494176;0.715248;-0.494176;,
  0.707107;0.000001;-0.707107;,
  0.494174;-0.715250;-0.494175;,
  0.000000;-1.000000;-0.000001;,
  -0.494176;-0.715248;0.494176;,
  -0.000000;0.000001;1.000000;,
  -0.000000;0.715247;0.698872;,
  0.000000;1.000000;-0.000001;,
  -0.000000;0.715247;-0.698871;,
  -0.000000;0.000001;-1.000000;,
  -0.000000;-0.715250;-0.698869;,
  0.000000;-1.000000;-0.000001;,
  -0.000000;-0.715249;0.698870;,
  0.707107;0.000001;0.707107;,
  0.494178;0.715246;0.494178;,
  -0.000000;1.000000;-0.000001;,
  -0.494176;0.715247;-0.494177;,
  -0.707107;0.000001;-0.707107;,
  -0.494175;-0.715250;-0.494175;,
  -0.000000;-1.000000;-0.000000;,
  0.494176;-0.715249;0.494176;,
  1.000000;0.000001;0.000000;,
  0.698873;0.715246;0.000000;,
  0.000000;1.000000;0.000000;,
  -0.698872;0.715247;0.000000;,
  -1.000000;0.000001;0.000000;,
  -0.698869;-0.715249;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.698871;-0.715248;0.000000;,
  0.707107;0.000001;-0.707107;,
  0.494178;0.715246;-0.494178;,
  0.000000;1.000000;-0.000000;,
  -0.494177;0.715247;0.494177;,
  -0.707107;0.000001;0.707107;,
  -0.494175;-0.715250;0.494175;,
  0.000000;-1.000000;-0.000000;,
  0.494176;-0.715248;-0.494176;,
  -0.000000;0.000001;-1.000000;,
  -0.000000;0.715246;-0.698873;,
  0.000000;1.000000;-0.000000;,
  0.000000;0.715248;0.698871;,
  0.000000;0.000001;1.000000;,
  0.000000;-0.715250;0.698868;,
  0.000000;-1.000000;-0.000001;,
  -0.000000;-0.715248;-0.698871;,
  -0.707107;0.000001;-0.707107;,
  -0.494178;0.715245;-0.494178;,
  -0.000000;1.000000;-0.000000;,
  0.494177;0.715247;0.494177;,
  0.707107;0.000001;0.707106;,
  0.494176;-0.715249;0.494175;,
  -0.000000;-1.000000;-0.000000;,
  -0.494177;-0.715248;-0.494177;;
  128;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  3;49,50,57;,
  3;50,51,57;,
  3;51,52,57;,
  3;52,53,57;,
  3;53,54,57;,
  3;54,55,57;,
  3;55,56,57;,
  3;56,49,57;,
  4;58,59,67,66;,
  4;59,60,68,67;,
  4;60,61,69,68;,
  4;61,62,70,69;,
  4;62,63,71,70;,
  4;63,64,72,71;,
  4;64,65,73,72;,
  4;65,58,66,73;,
  4;66,67,75,74;,
  4;67,68,76,75;,
  4;68,69,77,76;,
  4;69,70,78,77;,
  4;70,71,79,78;,
  4;71,72,80,79;,
  4;72,73,81,80;,
  4;73,66,74,81;,
  4;74,75,83,82;,
  4;75,76,84,83;,
  4;76,77,85,84;,
  4;77,78,86,85;,
  4;78,79,87,86;,
  4;79,80,88,87;,
  4;80,81,89,88;,
  4;81,74,82,89;,
  4;82,83,91,90;,
  4;83,84,92,91;,
  4;84,85,93,92;,
  4;85,86,94,93;,
  4;86,87,95,94;,
  4;87,88,96,95;,
  4;88,89,97,96;,
  4;89,82,90,97;,
  4;90,91,99,98;,
  4;91,92,100,99;,
  4;92,93,101,100;,
  4;93,94,102,101;,
  4;94,95,103,102;,
  4;95,96,104,103;,
  4;96,97,105,104;,
  4;97,90,98,105;,
  4;98,99,107,106;,
  4;99,100,108,107;,
  4;100,101,109,108;,
  4;101,102,110,109;,
  4;102,103,111,110;,
  4;103,104,112,111;,
  4;104,105,113,112;,
  4;105,98,106,113;,
  4;106,107,115,114;,
  4;107,108,116,115;,
  4;108,109,117,116;,
  4;109,110,118,117;,
  4;110,111,119,118;,
  4;111,112,120,119;,
  4;112,113,121,120;,
  4;113,106,114,121;,
  4;114,115,59,58;,
  4;115,116,60,59;,
  4;116,117,61,60;,
  4;117,118,62,61;,
  4;118,119,63,62;,
  4;119,120,64,63;,
  4;120,121,65,64;,
  4;121,114,58,65;;
 }
 MeshTextureCoords {
  160;
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
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
  1.000000;1.000000;;
 }
}
