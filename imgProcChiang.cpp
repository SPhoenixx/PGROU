//
//  imgProcChiang.cpp
//  RandomDotMarkers
//
//  Created by Guillaume Moreau on 13/07/11.
//  Copyright 2011 Ecole Centrale de Nantes. All rights reserved.
//
#include "skeletonization/Skeletonize.h"
#include "skeletonization/Intersections.h"

#include <iostream>
#include <fstream>

using namespace std;

#include "imgProcChiang.h"

/**
 implémentation adaptée de Fast and Inexpensive Color Image Segmentation for
 interactive robots. J. Bruce, T. Balch, M. Veloso. Proc. IEEE/RSJ International
 Conference on Intelligent Robots and Systems, 2000.
*/
imgProcChiang::imgProcChiang(IplImage *src) : Skeletonize(src) {
   // initialisation de la threshold table à 0
   for (int i=0 ; i < 256 ; i++) {
      for (int j=0 ; j < 256 ; j++) {
         for (int k=0 ; k<256 ; k++) {
            thresTable[i][j][k] = false;
         }
      }
   }
   
   // remplissage avec les valeurs données dans le fichier
   // @bug: le dernier point sera lu en double (eof() positionné après tentative
   // de lecture. mais sans effet sur la suite...
   ifstream inf;
   inf.open("filters.dat");
   while (!inf.eof()) {
      int r,g,b;
      inf >> r >> g >> b;
      if (r>=0 && r<256 && g>=0 && g<256 && b>=0 && b<256) {
         thresTable[r][g][b] = true;
         // debug lecture
         cout << "ajout de (" << r << "," << g << "," << b << ")" << endl;
      }
      else {
         cerr << "pb a la lecture du fichier de filtrage" << endl;
      }
   }
   inf.close();
}

void imgProcChiang::processImage(IplImage *colorSrcImg, int threshold) {
   IplImage *graySrcImg = cvCreateImage(cvGetSize(colorSrcImg), IPL_DEPTH_8U, 1);
   //cout << "--frame " << colorSrcImg->nChannels <<endl;
   // seuillage rapide : parcours de l'ensemble des pixels et validation par la table
   uchar *redPointer = (uchar*) colorSrcImg->imageData;
   uchar *greyPointer = (uchar*) graySrcImg->imageData;
	uchar rr = 0;
	uchar gg = 0;
	uchar bb = 0;
   for (int y=0 ; y<colorSrcImg->height ; y++) {
      for (int x=0 ; x<colorSrcImg->width ; x++) {
         rr = (uchar) *redPointer++;
		
		 uchar test = (uchar) *redPointer;
		 int test1 = (int) *redPointer;
		 uchar* ptr = cvPtr2D(colorSrcImg, y, x, NULL);
		 //cout << "redPt" << (int) *ptr << "/" << (int) *ptr++ << (int) *ptr++ << endl;
         
		 gg = (uchar) *redPointer++;
         bb = (uchar) *redPointer++;

		 //BGR order!!!!!!!!!!!!!!!!!!in IplImage!!
		 if ((rr==105||rr==99||rr==92)&&(bb==105||bb==99||bb==92)&&(gg==105||gg==99||gg==92)) {
			cout << "P(" << x << "," << y << ")=" << (int)bb << "," << (int)gg << "," << (int)rr << ")" << endl;
			//cvWaitKey(0);
		 }

         if (thresTable[bb][gg][rr]) {
            //cout << "+ajout de (" << rr << "," << gg << "," << bb << ")" << endl;
            *greyPointer++ = 255;
         }
         else {
            *greyPointer++ = 0;
         }
      }
      //*redPointer += colorSrcImg->width;
   }
   // on montre le résultat
	cvShowImage("Color", colorSrcImg);
   cvShowImage("Clusterized", graySrcImg);

   Skeletonize::processImage1(graySrcImg);

   
   //cvReleaseImage(&graySrcImg);
}


