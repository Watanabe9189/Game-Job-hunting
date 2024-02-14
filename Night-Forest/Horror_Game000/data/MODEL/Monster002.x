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
 261;
 0.93502;273.20811;0.00000;,
 -24.68089;266.00210;25.61592;,
 0.93502;266.00210;36.22640;,
 -35.29138;266.00210;0.00000;,
 -24.68089;266.00210;-25.61592;,
 0.93502;266.00210;-36.22640;,
 26.55096;266.00210;-25.61592;,
 37.16140;266.00210;0.00000;,
 26.55096;266.00210;25.61592;,
 -46.39704;245.48150;47.33207;,
 0.93502;245.48150;66.93767;,
 -66.00260;245.48150;0.00000;,
 -46.39704;245.48150;-47.33207;,
 0.93502;245.48150;-66.93767;,
 48.26709;245.48150;-47.33206;,
 67.87267;245.48150;0.00000;,
 26.55096;266.00210;25.61592;,
 48.26709;245.48150;47.33206;,
 0.93502;266.00210;36.22640;,
 0.93502;245.48150;66.93767;,
 -60.90728;214.77022;61.84232;,
 0.93502;214.77022;87.45834;,
 -86.52333;214.77022;0.00000;,
 -60.90731;214.77022;-61.84232;,
 0.93502;214.77022;-87.45834;,
 62.77735;214.77022;-61.84232;,
 88.39338;214.77022;0.00000;,
 62.77735;214.77022;61.84229;,
 0.93502;214.77022;87.45834;,
 -66.00260;178.54397;66.93767;,
 0.93502;178.54397;94.66415;,
 -93.72916;178.54397;0.00000;,
 -66.00260;178.54397;-66.93766;,
 0.93502;178.54397;-94.66415;,
 67.87267;178.54397;-66.93767;,
 95.59915;178.54397;0.00000;,
 67.87267;178.54397;66.93766;,
 0.93502;178.54397;94.66415;,
 -60.90728;142.31764;61.84232;,
 0.93502;142.31764;87.45834;,
 -86.52333;142.31764;0.00000;,
 -93.72916;178.54397;0.00000;,
 -66.00260;178.54397;-66.93766;,
 -60.90731;142.31764;-61.84232;,
 -86.52333;142.31764;0.00000;,
 0.93502;178.54397;-94.66415;,
 0.93502;142.31764;-87.45834;,
 67.87267;178.54397;-66.93767;,
 62.77735;142.31764;-61.84232;,
 95.59915;178.54397;0.00000;,
 88.39338;142.31764;0.00000;,
 62.77735;142.31764;61.84229;,
 88.39338;142.31764;0.00000;,
 0.93502;142.31764;87.45834;,
 -46.39704;111.60636;47.33207;,
 0.93502;111.60636;66.93767;,
 -66.00260;111.60636;0.00000;,
 -46.39704;111.60636;-47.33207;,
 -66.00260;111.60636;0.00000;,
 0.93502;111.60636;-66.93767;,
 48.26709;111.60636;-47.33206;,
 67.87267;111.60636;0.00000;,
 48.26709;111.60636;47.33206;,
 67.87267;111.60636;0.00000;,
 0.93502;111.60636;66.93767;,
 -24.68089;91.08572;25.61592;,
 0.93502;91.08572;36.22640;,
 -35.29138;91.08572;0.00000;,
 -24.68089;91.08572;-25.61592;,
 -35.29138;91.08572;0.00000;,
 0.93502;91.08572;-36.22640;,
 26.55096;91.08572;-25.61592;,
 37.16140;91.08572;0.00000;,
 26.55096;91.08572;25.61592;,
 37.16140;91.08572;0.00000;,
 0.93502;91.08572;36.22640;,
 0.93502;83.87988;0.00000;,
 -24.68089;91.08572;-25.61592;,
 0.93502;91.08572;-36.22640;,
 26.55096;91.08572;-25.61592;,
 0.93502;83.87988;0.00000;,
 35.79522;132.46978;-49.06067;,
 59.37343;132.46978;-49.06067;,
 59.37343;7.54918;-22.48874;,
 35.79522;7.54918;-22.48874;,
 59.37343;132.46978;-49.06067;,
 59.37343;132.46978;-25.48251;,
 59.37343;7.54918;1.08939;,
 59.37343;7.54918;-22.48874;,
 59.37343;132.46978;-25.48251;,
 35.79522;132.46978;-25.48251;,
 35.79522;7.54918;1.08939;,
 59.37343;7.54918;1.08939;,
 35.79522;132.46978;-25.48251;,
 35.79522;132.46978;-49.06067;,
 35.79522;7.54918;-22.48874;,
 35.79522;7.54918;1.08939;,
 59.37343;132.46978;-49.06067;,
 35.79522;132.46978;-49.06067;,
 35.79522;7.54918;-22.48874;,
 59.37343;7.54918;-22.48874;,
 -58.98303;132.46978;-49.06067;,
 -35.40487;132.46978;-49.06067;,
 -35.40487;7.54918;-22.48874;,
 -58.98303;7.54918;-22.48874;,
 -35.40487;132.46978;-49.06067;,
 -35.40487;132.46978;-25.48251;,
 -35.40487;7.54918;1.08939;,
 -35.40487;7.54918;-22.48874;,
 -35.40487;132.46978;-25.48251;,
 -58.98303;132.46978;-25.48251;,
 -58.98303;7.54918;1.08939;,
 -35.40487;7.54918;1.08939;,
 -58.98303;132.46978;-25.48251;,
 -58.98303;132.46978;-49.06067;,
 -58.98303;7.54918;-22.48874;,
 -58.98303;7.54918;1.08939;,
 -35.40487;132.46978;-49.06067;,
 -58.98303;132.46978;-49.06067;,
 -58.98303;7.54918;-22.48874;,
 -35.40487;7.54918;-22.48874;,
 -8.98894;132.46978;-49.06067;,
 14.58922;132.46978;-49.06067;,
 14.58922;7.54918;-22.48874;,
 -8.98894;7.54918;-22.48874;,
 14.58922;132.46978;-49.06067;,
 14.58922;132.46978;-25.48251;,
 14.58922;7.54918;1.08939;,
 14.58922;7.54918;-22.48874;,
 14.58922;132.46978;-25.48251;,
 -8.98894;132.46978;-25.48251;,
 -8.98894;7.54918;1.08939;,
 14.58922;7.54918;1.08939;,
 -8.98894;132.46978;-25.48251;,
 -8.98894;132.46978;-49.06067;,
 -8.98894;7.54918;-22.48874;,
 -8.98894;7.54918;1.08939;,
 14.58922;132.46978;-49.06067;,
 -8.98894;132.46978;-49.06067;,
 -8.98894;7.54918;-22.48874;,
 14.58922;7.54918;-22.48874;,
 35.79522;132.46978;-8.38484;,
 59.37343;132.46978;-8.38484;,
 59.37343;8.35945;15.20312;,
 35.79522;8.35945;15.20312;,
 59.37343;132.46978;-8.38484;,
 59.37343;132.46978;15.19332;,
 59.37343;8.35945;38.78127;,
 59.37343;8.35945;15.20312;,
 59.37343;132.46978;15.19332;,
 35.79522;132.46978;15.19332;,
 35.79522;8.35945;38.78127;,
 59.37343;8.35945;38.78127;,
 35.79522;132.46978;15.19332;,
 35.79522;132.46978;-8.38484;,
 35.79522;8.35945;15.20312;,
 35.79522;8.35945;38.78127;,
 59.37343;132.46978;-8.38484;,
 35.79522;132.46978;-8.38484;,
 35.79522;8.35945;15.20312;,
 59.37343;8.35945;15.20312;,
 -58.98303;132.46978;-8.38484;,
 -35.40487;132.46978;-8.38484;,
 -35.40487;8.35945;15.20312;,
 -58.98303;8.35945;15.20312;,
 -35.40487;132.46978;-8.38484;,
 -35.40487;132.46978;15.19332;,
 -35.40487;8.35945;38.78127;,
 -35.40487;8.35945;15.20312;,
 -35.40487;132.46978;15.19332;,
 -58.98303;132.46978;15.19332;,
 -58.98303;8.35945;38.78127;,
 -35.40487;8.35945;38.78127;,
 -58.98303;132.46978;15.19332;,
 -58.98303;132.46978;-8.38484;,
 -58.98303;8.35945;15.20312;,
 -58.98303;8.35945;38.78127;,
 -35.40487;132.46978;-8.38484;,
 -58.98303;132.46978;-8.38484;,
 -58.98303;8.35945;15.20312;,
 -35.40487;8.35945;15.20312;,
 -8.98894;132.46978;-8.38484;,
 14.58922;132.46978;-8.38484;,
 14.58922;8.35945;15.20312;,
 -8.98894;8.35945;15.20312;,
 14.58922;132.46978;-8.38484;,
 14.58922;132.46978;15.19332;,
 14.58922;8.35945;38.78127;,
 14.58922;8.35945;15.20312;,
 14.58922;132.46978;15.19332;,
 -8.98894;132.46978;15.19332;,
 -8.98894;8.35945;38.78127;,
 14.58922;8.35945;38.78127;,
 -8.98894;132.46978;15.19332;,
 -8.98894;132.46978;-8.38484;,
 -8.98894;8.35945;15.20312;,
 -8.98894;8.35945;38.78127;,
 14.58922;132.46978;-8.38484;,
 -8.98894;132.46978;-8.38484;,
 -8.98894;8.35945;15.20312;,
 14.58922;8.35945;15.20312;,
 35.79522;132.46978;29.12524;,
 59.37343;132.46978;29.12524;,
 59.37343;8.35945;52.71318;,
 35.79522;8.35945;52.71318;,
 59.37343;132.46978;29.12524;,
 59.37343;132.46978;52.70339;,
 59.37343;8.35945;76.29133;,
 59.37343;8.35945;52.71318;,
 59.37343;132.46978;52.70339;,
 35.79522;132.46978;52.70339;,
 35.79522;8.35945;76.29133;,
 59.37343;8.35945;76.29133;,
 35.79522;132.46978;52.70339;,
 35.79522;132.46978;29.12524;,
 35.79522;8.35945;52.71318;,
 35.79522;8.35945;76.29133;,
 59.37343;132.46978;29.12524;,
 35.79522;132.46978;29.12524;,
 35.79522;8.35945;52.71318;,
 59.37343;8.35945;52.71318;,
 -58.98303;132.46978;29.12524;,
 -35.40487;132.46978;29.12524;,
 -35.40487;8.35945;52.71318;,
 -58.98303;8.35945;52.71318;,
 -35.40487;132.46978;29.12524;,
 -35.40487;132.46978;52.70339;,
 -35.40487;8.35945;76.29133;,
 -35.40487;8.35945;52.71318;,
 -35.40487;132.46978;52.70339;,
 -58.98303;132.46978;52.70339;,
 -58.98303;8.35945;76.29133;,
 -35.40487;8.35945;76.29133;,
 -58.98303;132.46978;52.70339;,
 -58.98303;132.46978;29.12524;,
 -58.98303;8.35945;52.71318;,
 -58.98303;8.35945;76.29133;,
 -35.40487;132.46978;29.12524;,
 -58.98303;132.46978;29.12524;,
 -58.98303;8.35945;52.71318;,
 -35.40487;8.35945;52.71318;,
 -8.98894;132.46978;29.12524;,
 14.58922;132.46978;29.12524;,
 14.58922;8.35945;52.71318;,
 -8.98894;8.35945;52.71318;,
 14.58922;132.46978;29.12524;,
 14.58922;132.46978;52.70339;,
 14.58922;8.35945;76.29133;,
 14.58922;8.35945;52.71318;,
 14.58922;132.46978;52.70339;,
 -8.98894;132.46978;52.70339;,
 -8.98894;8.35945;76.29133;,
 14.58922;8.35945;76.29133;,
 -8.98894;132.46978;52.70339;,
 -8.98894;132.46978;29.12524;,
 -8.98894;8.35945;52.71318;,
 -8.98894;8.35945;76.29133;,
 14.58922;132.46978;29.12524;,
 -8.98894;132.46978;29.12524;,
 -8.98894;8.35945;52.71318;,
 14.58922;8.35945;52.71318;;
 
 118;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,2,8;,
 4;2,1,9,10;,
 4;1,3,11,9;,
 4;3,4,12,11;,
 4;4,5,13,12;,
 4;5,6,14,13;,
 4;6,7,15,14;,
 4;7,16,17,15;,
 4;16,18,19,17;,
 4;10,9,20,21;,
 4;9,11,22,20;,
 4;11,12,23,22;,
 4;12,13,24,23;,
 4;13,14,25,24;,
 4;14,15,26,25;,
 4;15,17,27,26;,
 4;17,19,28,27;,
 4;21,20,29,30;,
 4;20,22,31,29;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;25,26,35,34;,
 4;26,27,36,35;,
 4;27,28,37,36;,
 4;30,29,38,39;,
 4;29,31,40,38;,
 4;41,42,43,44;,
 4;42,45,46,43;,
 4;45,47,48,46;,
 4;47,49,50,48;,
 4;35,36,51,52;,
 4;36,37,53,51;,
 4;39,38,54,55;,
 4;38,40,56,54;,
 4;44,43,57,58;,
 4;43,46,59,57;,
 4;46,48,60,59;,
 4;48,50,61,60;,
 4;52,51,62,63;,
 4;51,53,64,62;,
 4;55,54,65,66;,
 4;54,56,67,65;,
 4;58,57,68,69;,
 4;57,59,70,68;,
 4;59,60,71,70;,
 4;60,61,72,71;,
 4;63,62,73,74;,
 4;62,64,75,73;,
 3;66,65,76;,
 3;65,67,76;,
 3;67,77,76;,
 3;77,78,76;,
 3;78,79,76;,
 3;79,74,76;,
 3;74,73,76;,
 3;73,75,80;,
 4;81,82,83,84;,
 4;85,86,87,88;,
 4;89,90,91,92;,
 4;93,94,95,96;,
 4;93,86,97,98;,
 4;99,100,87,96;,
 4;101,102,103,104;,
 4;105,106,107,108;,
 4;109,110,111,112;,
 4;113,114,115,116;,
 4;113,106,117,118;,
 4;119,120,107,116;,
 4;121,122,123,124;,
 4;125,126,127,128;,
 4;129,130,131,132;,
 4;133,134,135,136;,
 4;133,126,137,138;,
 4;139,140,127,136;,
 4;141,142,143,144;,
 4;145,146,147,148;,
 4;149,150,151,152;,
 4;153,154,155,156;,
 4;153,146,157,158;,
 4;159,160,147,156;,
 4;161,162,163,164;,
 4;165,166,167,168;,
 4;169,170,171,172;,
 4;173,174,175,176;,
 4;173,166,177,178;,
 4;179,180,167,176;,
 4;181,182,183,184;,
 4;185,186,187,188;,
 4;189,190,191,192;,
 4;193,194,195,196;,
 4;193,186,197,198;,
 4;199,200,187,196;,
 4;201,202,203,204;,
 4;205,206,207,208;,
 4;209,210,211,212;,
 4;213,214,215,216;,
 4;213,206,217,218;,
 4;219,220,207,216;,
 4;221,222,223,224;,
 4;225,226,227,228;,
 4;229,230,231,232;,
 4;233,234,235,236;,
 4;233,226,237,238;,
 4;239,240,227,236;,
 4;241,242,243,244;,
 4;245,246,247,248;,
 4;249,250,251,252;,
 4;253,254,255,256;,
 4;253,246,257,258;,
 4;259,260,247,256;;
 
 MeshMaterialList {
  5;
  118;
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
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  1,
  1,
  1,
  1,
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
  3,
  3,
  3,
  3,
  4,
  0,
  3,
  3,
  3,
  3,
  4,
  0,
  3,
  3,
  3,
  3,
  4,
  0,
  3,
  3,
  3,
  3,
  4,
  0,
  3,
  3,
  3,
  3,
  4,
  0,
  3,
  3,
  3,
  3,
  4,
  0,
  3,
  3,
  3,
  3,
  4,
  0,
  3,
  3,
  3,
  3,
  4,
  0,
  3,
  3,
  3,
  3,
  4,
  0;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.280000;0.280000;0.280000;;
   TextureFilename {
    "data\\TEXTURE\\Eye001.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\Teeth000.png";
   }
  }
  Material {
   0.633600;0.000000;0.068800;1.000000;;
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
  83;
  0.000000;1.000000;0.000000;,
  -0.000000;0.924735;0.380612;,
  -0.269134;0.924735;0.269134;,
  -0.380612;0.924735;0.000000;,
  -0.269134;0.924735;-0.269134;,
  -0.000000;0.924735;-0.380612;,
  0.269134;0.924735;-0.269133;,
  0.380612;0.924735;0.000000;,
  0.269134;0.924735;0.269133;,
  0.000000;0.709231;0.704977;,
  -0.498494;0.709230;0.498494;,
  -0.704976;0.709231;0.000000;,
  -0.498494;0.709231;-0.498494;,
  -0.000000;0.709231;-0.704977;,
  0.498494;0.709231;-0.498494;,
  0.704976;0.709231;0.000000;,
  0.498494;0.709230;0.498494;,
  0.000000;0.384551;0.923104;,
  -0.652733;0.384551;0.652733;,
  -0.923104;0.384551;0.000000;,
  -0.652733;0.384551;-0.652733;,
  -0.000000;0.384551;-0.923104;,
  0.652733;0.384551;-0.652733;,
  0.923104;0.384551;0.000000;,
  0.652733;0.384551;0.652733;,
  0.000000;0.000000;1.000000;,
  -0.707107;0.000000;0.707107;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.000000;-0.707107;,
  -0.000000;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;0.000000;,
  0.707107;0.000000;0.707107;,
  0.000000;-0.384551;0.923104;,
  -0.652733;-0.384551;0.652733;,
  -0.923104;-0.384551;0.000000;,
  -0.652733;-0.384551;-0.652733;,
  -0.000000;-0.384551;-0.923104;,
  0.652733;-0.384551;-0.652733;,
  0.923104;-0.384551;0.000000;,
  0.652733;-0.384551;0.652733;,
  0.000000;-0.709230;0.704977;,
  -0.498494;-0.709230;0.498494;,
  -0.704977;-0.709230;0.000000;,
  -0.498494;-0.709230;-0.498494;,
  0.000000;-0.709230;-0.704977;,
  0.498494;-0.709230;-0.498494;,
  0.704977;-0.709230;0.000000;,
  0.498494;-0.709230;0.498494;,
  -0.000000;-0.924735;0.380611;,
  -0.269132;-0.924735;0.269132;,
  -0.380611;-0.924735;0.000000;,
  -0.269132;-0.924735;-0.269132;,
  -0.000000;-0.924735;-0.380611;,
  0.269132;-0.924735;-0.269132;,
  0.380611;-0.924735;-0.000000;,
  0.269132;-0.924735;0.269132;,
  -0.000000;-1.000000;0.000000;,
  0.000000;-0.208056;-0.978117;,
  1.000000;0.000000;-0.000000;,
  0.000000;0.208056;0.978117;,
  0.000000;-0.208056;-0.978117;,
  0.000000;-0.208056;-0.978117;,
  0.000000;0.208056;0.978117;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.186714;-0.982414;,
  1.000000;0.000000;-0.000000;,
  0.000000;0.186714;0.982414;,
  0.000000;0.186714;0.982414;,
  0.000000;-0.186714;-0.982414;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.186714;-0.982414;,
  1.000000;0.000000;-0.000000;,
  0.000000;0.186714;0.982414;,
  0.000000;0.186714;0.982414;,
  0.000000;-0.186714;-0.982414;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  118;
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
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;60,60,60,60;,
  4;64,64,64,64;,
  4;65,65,65,65;,
  4;66,66,66,66;,
  4;61,61,61,61;,
  4;59,59,59,59;,
  4;60,60,60,60;,
  4;64,64,64,64;,
  4;65,65,65,65;,
  4;66,66,66,66;,
  4;62,62,62,62;,
  4;59,59,59,59;,
  4;63,63,63,63;,
  4;64,64,64,64;,
  4;65,65,65,65;,
  4;66,66,66,66;,
  4;67,67,67,67;,
  4;68,68,68,68;,
  4;69,69,69,69;,
  4;72,72,72,72;,
  4;73,73,73,73;,
  4;74,74,74,74;,
  4;67,67,67,67;,
  4;68,68,68,68;,
  4;70,70,70,70;,
  4;72,72,72,72;,
  4;73,73,73,73;,
  4;74,74,74,74;,
  4;71,71,71,71;,
  4;68,68,68,68;,
  4;70,70,70,70;,
  4;72,72,72,72;,
  4;73,73,73,73;,
  4;74,74,74,74;,
  4;75,75,75,75;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  4;80,80,80,80;,
  4;81,81,81,81;,
  4;82,82,82,82;,
  4;75,75,75,75;,
  4;76,76,76,76;,
  4;78,78,78,78;,
  4;80,80,80,80;,
  4;81,81,81,81;,
  4;82,82,82,82;,
  4;79,79,79,79;,
  4;76,76,76,76;,
  4;78,78,78,78;,
  4;80,80,80,80;,
  4;81,81,81,81;,
  4;82,82,82,82;;
 }
 MeshTextureCoords {
  261;
  0.252780;0.019700;,
  0.135460;0.264500;,
  0.014190;0.256850;,
  0.252780;0.267450;,
  0.370090;0.264500;,
  0.491370;0.256850;,
  0.619270;0.248380;,
  0.752780;0.244590;,
  -0.113720;0.248380;,
  0.132030;0.434910;,
  0.008960;0.433200;,
  0.252780;0.435580;,
  0.373520;0.434910;,
  0.496590;0.433200;,
  0.623280;0.431350;,
  0.752780;0.430530;,
  0.886280;0.248380;,
  0.882270;0.431350;,
  1.014190;0.256850;,
  1.008960;0.433200;,
  0.131060;0.557950;,
  0.007510;0.559130;,
  0.252780;0.557480;,
  0.374500;0.557950;,
  0.498040;0.559130;,
  0.624360;0.560380;,
  0.752780;0.560930;,
  0.881200;0.560380;,
  1.007510;0.559130;,
  0.130810;0.659000;,
  0.007150;0.661570;,
  0.252780;0.657980;,
  0.374740;0.659000;,
  0.498400;0.661570;,
  0.624620;0.664260;,
  0.752780;0.665410;,
  0.880930;0.664260;,
  1.007150;0.661570;,
  0.131060;0.749250;,
  0.007510;0.752520;,
  0.252780;0.747930;,
  0.009170;0.069720;,
  0.151780;0.069720;,
  0.177990;0.506910;,
  0.046240;0.506910;,
  0.496070;0.069720;,
  0.496070;0.506910;,
  0.840350;0.069720;,
  0.814140;0.506910;,
  0.982960;0.069720;,
  0.945890;0.506910;,
  0.881200;0.755940;,
  0.752780;0.757400;,
  1.007510;0.752520;,
  0.132030;0.833840;,
  0.008960;0.837490;,
  0.252780;0.832370;,
  0.252620;0.877540;,
  0.151780;0.877540;,
  0.496070;0.877540;,
  0.739510;0.877540;,
  0.840350;0.877540;,
  0.882270;0.841290;,
  0.752780;0.842910;,
  1.008960;0.837490;,
  0.135460;0.915470;,
  0.014190;0.919270;,
  0.252780;0.913960;,
  0.364310;1.125180;,
  0.309740;1.125180;,
  0.496070;1.125180;,
  0.627820;1.125180;,
  0.682390;1.125180;,
  0.886280;0.923300;,
  0.752780;0.925040;,
  1.014190;0.919270;,
  0.252780;0.994380;,
  0.370090;0.915470;,
  0.491370;0.919270;,
  0.619270;0.923300;,
  1.252780;0.994380;,
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
  1.000000;0.000000;;
 }
}