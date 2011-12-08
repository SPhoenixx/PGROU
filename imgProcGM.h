//
//  imgProcGM.h
//  RandomDotMarkers
//
//  Created by Guillaume Moreau on 19/05/11.
//  Copyright 2011 Ecole Centrale de Nantes. All rights reserved.
//


#include "skeletonization/Skeletonize.h"

class imgProcGM : public Skeletonize {
public:
   // constructor
   imgProcGM(IplImage *src);

   void processImage(IplImage *colorSrcImg, int threshold=230);
};
