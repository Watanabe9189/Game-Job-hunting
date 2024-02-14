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
 154;
 14.07458;82.39721;16.74596;,
 15.49017;81.96166;-17.03647;,
 -14.64503;86.92327;-5.85784;,
 14.07458;82.39721;16.74596;,
 37.63863;69.57443;0.33577;,
 15.49017;81.96166;-17.03647;,
 14.07458;82.39721;16.74596;,
 -26.08936;69.57443;26.73276;,
 0.30767;69.57443;37.66675;,
 -14.64503;86.92327;-5.85784;,
 -37.02332;69.57443;0.33577;,
 -26.08936;69.57443;-26.06122;,
 0.30767;69.57443;-36.99520;,
 15.49017;81.96166;-17.03647;,
 31.44501;53.38972;-30.80160;,
 0.30767;69.57443;-36.99520;,
 37.63863;69.57443;0.33577;,
 14.07458;82.39721;16.74596;,
 31.44501;53.38972;31.47313;,
 0.30767;32.15877;-41.21829;,
 41.86173;32.15877;0.33577;,
 31.44501;53.38972;-30.80160;,
 0.30767;69.57443;37.66675;,
 0.30767;32.15877;41.88986;,
 31.44501;53.38972;31.47313;,
 -26.08936;69.57443;26.73276;,
 -29.07554;32.15877;29.71894;,
 -37.02332;69.57443;0.33577;,
 -43.72727;35.87156;0.33577;,
 -26.08936;69.57443;-26.06122;,
 -29.07554;32.15877;-29.04739;,
 0.30767;69.57443;-36.99520;,
 0.30767;32.15877;-41.21829;,
 26.70466;19.68687;-26.06122;,
 0.30767;32.15877;-41.21829;,
 26.70466;19.68687;26.73277;,
 41.86173;32.15877;0.33577;,
 -43.72727;35.87156;0.33577;,
 -10.81505;4.60107;2.36520;,
 -29.07554;32.15877;29.71894;,
 -29.07554;32.15877;-29.04739;,
 26.70466;19.68687;-26.06122;,
 -10.81505;4.60107;2.36520;,
 0.30767;32.15877;-41.21829;,
 41.86173;32.15877;0.33577;,
 -10.81505;4.60107;2.36520;,
 26.70466;19.68687;26.73277;,
 -10.81505;4.60107;2.36520;,
 0.30767;32.15877;41.88986;,
 -10.81505;4.60107;2.36520;,
 -10.81505;4.60107;2.36520;,
 0.30767;32.15877;-41.21829;,
 -10.81505;4.60107;2.36520;,
 -29.07554;32.15877;-29.04739;,
 1.67494;54.01424;-58.34008;,
 51.29441;54.01424;-29.54901;,
 51.29441;45.44781;-29.54901;,
 1.67494;45.44781;-58.34008;,
 33.69871;54.01424;-15.16731;,
 1.67494;54.01424;-19.91720;,
 1.67494;45.44781;-19.91720;,
 33.69871;45.44781;-15.16731;,
 51.29441;54.01424;28.03316;,
 51.29441;45.44781;28.03316;,
 33.69868;54.01424;22.27494;,
 33.69868;45.44781;22.27494;,
 1.67494;54.01424;56.82425;,
 1.67494;45.44781;56.82425;,
 1.67494;54.01424;45.30781;,
 1.67494;45.44781;45.30781;,
 -47.94466;54.01424;28.03315;,
 -47.94466;45.44781;28.03315;,
 -30.35975;54.01424;22.27493;,
 -30.35975;45.44781;22.27493;,
 -47.94466;54.01424;-29.54901;,
 -47.94466;45.44781;-29.54901;,
 -30.35975;54.01424;-5.50781;,
 -30.35975;45.44781;-5.50781;,
 1.67494;54.01424;-58.34008;,
 1.67494;45.44781;-58.34008;,
 1.67494;54.01424;-19.91720;,
 1.67494;45.44781;-19.91720;,
 33.69871;54.01424;-15.16731;,
 51.29441;54.01424;-29.54901;,
 1.67494;45.44781;-58.34008;,
 51.29441;45.44781;-29.54901;,
 33.69871;45.44781;-15.16731;,
 1.67494;45.44781;-19.91720;,
 33.69868;54.01424;22.27494;,
 51.29441;54.01424;28.03316;,
 51.29441;45.44781;28.03316;,
 33.69868;45.44781;22.27494;,
 1.67494;54.01424;45.30781;,
 1.67494;54.01424;56.82425;,
 1.67494;45.44781;56.82425;,
 1.67494;45.44781;45.30781;,
 -30.35975;54.01424;22.27493;,
 -47.94466;54.01424;28.03315;,
 -47.94466;45.44781;28.03315;,
 -30.35975;45.44781;22.27493;,
 -30.35975;54.01424;-5.50781;,
 -47.94466;54.01424;-29.54901;,
 -47.94466;45.44781;-29.54901;,
 -30.35975;45.44781;-5.50781;,
 1.67494;95.81881;3.52530;,
 51.29441;78.52212;3.52530;,
 51.29441;78.52212;-5.04113;,
 1.67494;95.81881;-5.04113;,
 35.50445;68.70915;3.52530;,
 1.67494;80.24761;3.52530;,
 1.67494;80.24761;-5.04113;,
 35.50445;68.70915;-5.04113;,
 51.29441;20.93995;3.52529;,
 51.29441;20.93995;-5.04114;,
 35.50444;26.69817;3.52530;,
 35.50444;26.69817;-5.04114;,
 1.67494;0.64276;3.52529;,
 1.67494;0.64276;-5.04114;,
 1.67494;12.15923;3.52529;,
 1.67494;12.15923;-5.04114;,
 -43.00993;20.93996;3.52529;,
 -43.00993;20.93996;-5.04114;,
 -22.91205;26.69817;3.52530;,
 -22.91205;26.69817;-5.04114;,
 -50.75320;78.52212;3.52530;,
 -50.75320;78.52212;-5.04113;,
 -30.24734;72.76390;3.52530;,
 -30.24734;72.76390;-5.04113;,
 1.67494;95.81881;3.52530;,
 1.67494;95.81881;-5.04113;,
 1.67494;80.24761;3.52530;,
 1.67494;80.24761;-5.04113;,
 35.50445;68.70915;3.52530;,
 51.29441;78.52212;3.52530;,
 1.67494;95.81881;-5.04113;,
 51.29441;78.52212;-5.04113;,
 35.50445;68.70915;-5.04113;,
 1.67494;80.24761;-5.04113;,
 35.50444;26.69817;3.52530;,
 51.29441;20.93995;3.52529;,
 51.29441;20.93995;-5.04114;,
 35.50444;26.69817;-5.04114;,
 1.67494;12.15923;3.52529;,
 1.67494;0.64276;3.52529;,
 1.67494;0.64276;-5.04114;,
 1.67494;12.15923;-5.04114;,
 -22.91205;26.69817;3.52530;,
 -43.00993;20.93996;3.52529;,
 -43.00993;20.93996;-5.04114;,
 -22.91205;26.69817;-5.04114;,
 -30.24734;72.76390;3.52530;,
 -50.75320;78.52212;3.52530;,
 -50.75320;78.52212;-5.04113;,
 -30.24734;72.76390;-5.04113;;
 
 84;
 3;0,1,2;,
 3;3,4,5;,
 3;6,7,8;,
 3;9,10,7;,
 3;9,7,6;,
 3;2,11,10;,
 3;1,12,11;,
 3;1,11,2;,
 3;13,14,15;,
 3;13,16,14;,
 3;17,18,16;,
 3;8,18,17;,
 3;14,19,15;,
 3;16,20,21;,
 3;18,20,16;,
 3;22,23,24;,
 3;25,26,23;,
 3;25,23,22;,
 3;27,28,26;,
 3;27,26,25;,
 3;29,30,28;,
 3;29,28,27;,
 3;29,31,32;,
 3;29,32,30;,
 3;21,33,34;,
 3;20,33,21;,
 3;24,35,36;,
 3;23,35,24;,
 3;37,38,39;,
 3;40,38,37;,
 3;41,42,43;,
 3;44,45,41;,
 3;46,47,44;,
 3;48,49,46;,
 3;39,50,48;,
 3;51,52,53;,
 4;54,55,56,57;,
 4;58,59,60,61;,
 4;55,62,63,56;,
 4;64,58,61,65;,
 4;62,66,67,63;,
 4;68,64,65,69;,
 4;66,70,71,67;,
 4;72,68,69,73;,
 4;70,74,75,71;,
 4;76,72,73,77;,
 4;74,78,79,75;,
 4;80,76,77,81;,
 4;54,59,82,83;,
 4;84,85,86,87;,
 4;83,82,88,89;,
 4;85,90,91,86;,
 4;89,88,92,93;,
 4;90,94,95,91;,
 4;93,92,96,97;,
 4;94,98,99,95;,
 4;97,96,100,101;,
 4;98,102,103,99;,
 4;101,100,59,54;,
 4;102,84,87,103;,
 4;104,105,106,107;,
 4;108,109,110,111;,
 4;105,112,113,106;,
 4;114,108,111,115;,
 4;112,116,117,113;,
 4;118,114,115,119;,
 4;116,120,121,117;,
 4;122,118,119,123;,
 4;120,124,125,121;,
 4;126,122,123,127;,
 4;124,128,129,125;,
 4;130,126,127,131;,
 4;104,109,132,133;,
 4;134,135,136,137;,
 4;133,132,138,139;,
 4;135,140,141,136;,
 4;139,138,142,143;,
 4;140,144,145,141;,
 4;143,142,146,147;,
 4;144,148,149,145;,
 4;147,146,150,151;,
 4;148,152,153,149;,
 4;151,150,109,104;,
 4;152,134,137,153;;
 
 MeshMaterialList {
  3;
  84;
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
  0,
  1,
  1,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  1,
  1,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
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
  2;;
  Material {
   0.800000;0.793600;0.050400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.400000;0.396800;0.025200;;
  }
  Material {
   0.583200;0.586400;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.102060;0.102620;0.000000;;
  }
  Material {
   0.524000;0.520800;0.511200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  68;
  -0.298823;0.952703;-0.055328;,
  0.275360;0.873289;-0.401925;,
  0.254047;0.897509;0.360470;,
  -0.886750;0.451837;0.097558;,
  0.037941;0.489120;-0.871391;,
  0.692003;0.193399;-0.695506;,
  0.851415;0.524480;0.003784;,
  0.039538;0.496670;0.867038;,
  -0.510101;0.567930;0.645951;,
  -0.576366;0.481525;-0.660255;,
  0.999166;-0.040824;0.000000;,
  0.690476;0.203952;0.694007;,
  -0.739482;-0.256511;0.622389;,
  -0.076541;-0.282978;0.956068;,
  -0.969451;-0.228820;-0.088356;,
  -0.079925;-0.296712;-0.951617;,
  0.693520;-0.195090;-0.693520;,
  0.491908;-0.461263;0.738419;,
  -0.648913;-0.389248;-0.653757;,
  -0.262815;-0.964761;-0.012862;,
  0.213611;-0.951165;-0.222837;,
  0.463431;-0.886125;-0.003704;,
  0.462945;-0.874086;0.147161;,
  0.453302;-0.877868;-0.154485;,
  0.501872;0.000000;-0.864942;,
  1.000000;0.000000;0.000000;,
  0.501872;0.000000;0.864942;,
  -0.501871;0.000000;0.864942;,
  -1.000000;0.000000;0.000000;,
  0.137286;0.000000;0.990531;,
  -0.146719;0.000000;0.989178;,
  -0.889916;0.000000;-0.456125;,
  -0.583900;0.000000;-0.811825;,
  0.889879;0.000000;-0.456197;,
  -1.000000;0.000000;-0.000001;,
  0.583769;0.000000;-0.811920;,
  -0.501871;0.000000;-0.864943;,
  0.410217;0.000000;0.911988;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.008373;0.999965;0.000000;,
  0.329161;0.944274;0.000000;,
  1.000000;0.000000;0.000000;,
  -0.019037;-0.999819;0.000000;,
  -0.802662;-0.596434;0.000000;,
  -0.991079;-0.133274;0.000000;,
  -0.049193;-0.998789;0.000000;,
  -0.322816;-0.946462;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.064013;0.997949;0.000000;,
  0.826832;0.562449;0.000000;,
  0.987558;0.157254;0.000000;,
  0.378606;-0.925558;-0.000000;,
  -0.394850;0.918746;0.000000;,
  -0.313302;0.949653;0.000000;,
  0.228247;-0.973603;-0.000000;,
  -0.000000;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;0.000000;-1.000000;,
  -0.000000;-0.000000;1.000000;,
  0.000000;0.000000;-1.000000;,
  -0.000000;-0.000000;1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;-0.000000;1.000000;,
  -0.000000;0.000000;-1.000000;;
  84;
  3;2,1,0;,
  3;2,6,1;,
  3;2,8,7;,
  3;0,3,8;,
  3;0,8,2;,
  3;0,9,3;,
  3;1,4,9;,
  3;1,9,0;,
  3;1,5,4;,
  3;1,6,5;,
  3;2,11,6;,
  3;7,11,2;,
  3;5,15,4;,
  3;6,10,5;,
  3;11,10,6;,
  3;7,13,11;,
  3;8,12,13;,
  3;8,13,7;,
  3;3,14,12;,
  3;3,12,8;,
  3;9,18,14;,
  3;9,14,3;,
  3;9,4,15;,
  3;9,15,18;,
  3;5,16,15;,
  3;10,16,5;,
  3;11,17,10;,
  3;13,17,11;,
  3;14,19,12;,
  3;18,19,14;,
  3;20,19,15;,
  3;21,22,20;,
  3;23,19,21;,
  3;13,19,17;,
  3;12,19,13;,
  3;15,19,18;,
  4;24,24,24,24;,
  4;30,29,29,30;,
  4;25,25,25,25;,
  4;31,34,34,31;,
  4;26,26,26,26;,
  4;32,31,31,32;,
  4;27,27,27,27;,
  4;33,35,35,33;,
  4;28,28,28,28;,
  4;25,33,33,25;,
  4;36,36,36,36;,
  4;29,37,37,29;,
  4;38,38,38,38;,
  4;39,39,39,39;,
  4;38,38,38,38;,
  4;39,39,39,39;,
  4;38,38,38,38;,
  4;39,39,39,39;,
  4;38,38,38,38;,
  4;39,39,39,39;,
  4;38,38,38,38;,
  4;39,39,39,39;,
  4;38,38,38,38;,
  4;39,39,39,39;,
  4;40,41,41,40;,
  4;47,46,46,47;,
  4;42,42,42,42;,
  4;48,48,48,48;,
  4;52,43,43,52;,
  4;49,53,53,49;,
  4;43,44,44,43;,
  4;50,49,49,50;,
  4;44,45,45,44;,
  4;51,50,50,51;,
  4;54,40,40,54;,
  4;46,55,55,46;,
  4;56,56,57,57;,
  4;58,59,59,58;,
  4;57,57,60,60;,
  4;59,61,61,59;,
  4;60,60,62,62;,
  4;61,63,63,61;,
  4;62,62,64,64;,
  4;63,65,65,63;,
  4;64,64,66,66;,
  4;65,67,67,65;,
  4;66,66,56,56;,
  4;67,58,58,67;;
 }
 MeshTextureCoords {
  154;
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.875000;0.125000;,
  0.375000;0.125000;,
  0.250000;0.250000;,
  0.250000;0.125000;,
  0.625000;0.125000;,
  0.625000;0.250000;,
  0.500000;0.250000;,
  0.750000;0.125000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.250000;,
  0.375000;0.375000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.125000;0.500000;,
  0.500000;0.375000;,
  0.500000;0.500000;,
  0.375000;0.500000;,
  0.625000;0.375000;,
  0.625000;0.500000;,
  0.750000;0.375000;,
  0.750000;0.500000;,
  0.875000;0.375000;,
  0.875000;0.500000;,
  1.000000;0.375000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.375000;0.625000;,
  0.250000;0.625000;,
  0.750000;0.625000;,
  0.750000;0.750000;,
  0.625000;0.750000;,
  0.875000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.875000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.125000;0.875000;,
  0.375000;0.750000;,
  0.250000;0.875000;,
  0.500000;0.750000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  1.000000;0.750000;,
  0.875000;0.875000;,
  0.875000;0.750000;,
  0.000000;0.000000;,
  0.166667;0.000000;,
  0.166667;1.000000;,
  0.000000;1.000000;,
  0.166667;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.166667;1.000000;,
  0.333333;0.000000;,
  0.333333;1.000000;,
  0.333333;0.000000;,
  0.333333;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.666667;0.000000;,
  0.666667;1.000000;,
  0.666667;0.000000;,
  0.666667;1.000000;,
  0.833333;0.000000;,
  0.833333;1.000000;,
  0.833333;0.000000;,
  0.833333;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.166667;0.000000;,
  0.166667;1.000000;,
  0.000000;1.000000;,
  0.166667;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.166667;1.000000;,
  0.333333;0.000000;,
  0.333333;1.000000;,
  0.333333;0.000000;,
  0.333333;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.666667;0.000000;,
  0.666667;1.000000;,
  0.666667;0.000000;,
  0.666667;1.000000;,
  0.833333;0.000000;,
  0.833333;1.000000;,
  0.833333;0.000000;,
  0.833333;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
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