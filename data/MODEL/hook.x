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
 48;
 0.00000;1.16468;-6.40557;,
 0.00000;17.78409;-0.02610;,
 7.52080;1.16468;-0.02610;,
 0.00000;17.78409;-0.02610;,
 -0.00000;1.16468;6.35337;,
 0.00000;17.78409;-0.02610;,
 -7.52080;1.16468;-0.02610;,
 0.00000;17.78409;-0.02610;,
 0.00000;1.16468;-6.40557;,
 0.00000;1.16468;-0.02610;,
 0.00000;1.16468;-6.40557;,
 7.52080;1.16468;-0.02610;,
 -0.00000;1.16468;6.35337;,
 -7.52080;1.16468;-0.02610;,
 0.00000;1.94847;-7.74927;,
 5.47956;1.94847;-5.47956;,
 5.47956;-8.29641;-5.47956;,
 0.00000;-8.29641;-7.74927;,
 7.74927;1.94847;0.00000;,
 7.74927;-8.29641;0.00000;,
 5.47956;1.94847;5.47956;,
 5.47956;-8.29641;5.47956;,
 -0.00000;1.94847;7.74927;,
 -0.00000;-8.29641;7.74927;,
 -5.47956;1.94847;5.47956;,
 -5.47956;-8.29641;5.47956;,
 -7.74927;1.94847;-0.00000;,
 -7.74927;-8.29641;-0.00000;,
 -5.47956;1.94847;-5.47956;,
 -5.47956;-8.29641;-5.47956;,
 0.00000;1.94847;-7.74927;,
 0.00000;-8.29641;-7.74927;,
 0.00000;1.94847;0.00000;,
 0.00000;1.94847;0.00000;,
 0.00000;1.94847;0.00000;,
 0.00000;1.94847;0.00000;,
 0.00000;1.94847;0.00000;,
 0.00000;1.94847;0.00000;,
 0.00000;1.94847;0.00000;,
 0.00000;1.94847;0.00000;,
 0.00000;-8.29641;-0.00000;,
 0.00000;-8.29641;-0.00000;,
 0.00000;-8.29641;-0.00000;,
 0.00000;-8.29641;-0.00000;,
 0.00000;-8.29641;-0.00000;,
 0.00000;-8.29641;-0.00000;,
 0.00000;-8.29641;-0.00000;,
 0.00000;-8.29641;-0.00000;;
 
 32;
 3;0,1,2;,
 3;2,3,4;,
 3;4,5,6;,
 3;6,7,8;,
 3;9,10,11;,
 3;9,11,12;,
 3;9,12,13;,
 3;9,13,10;,
 4;14,15,16,17;,
 4;15,18,19,16;,
 4;18,20,21,19;,
 4;20,22,23,21;,
 4;22,24,25,23;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 3;32,15,14;,
 3;33,18,15;,
 3;34,20,18;,
 3;35,22,20;,
 3;36,24,22;,
 3;37,26,24;,
 3;38,28,26;,
 3;39,30,28;,
 3;40,17,16;,
 3;41,16,19;,
 3;42,19,21;,
 3;43,21,23;,
 3;44,23,25;,
 3;45,25,27;,
 3;46,27,29;,
 3;47,29,31;;
 
 MeshMaterialList {
  2;
  32;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  1;;
  Material {
   0.448627;0.448627;0.448627;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.326275;0.558431;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  15;
  0.620818;0.280939;-0.731887;,
  0.620818;0.280939;0.731887;,
  -0.620818;0.280940;0.731887;,
  0.000000;-1.000000;-0.000000;,
  -0.620818;0.280939;-0.731887;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;0.000000;,
  0.707107;0.000000;0.707107;,
  -0.000000;0.000000;1.000000;,
  -0.707107;0.000000;0.707107;,
  -1.000000;0.000000;-0.000000;,
  -0.707107;0.000000;-0.707107;,
  0.000000;-1.000000;-0.000000;;
  32;
  3;0,0,0;,
  3;1,1,1;,
  3;2,2,2;,
  3;4,4,4;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;13,6,6,13;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;;
 }
 MeshTextureCoords {
  48;
  0.000000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}
