/*
	This file is part of UCHIYAMARKERS, a software for random dot markers.
	Copyright (c) 2011 Hideaki Uchiyama

	You can use, copy, modify and re-distribute this software
	for non-profit purposes.
*/

#include "paperlist.h"

Paper* PaperList::FindPaper(const int paperid)
{
	paperlist::iterator found = m_papers.find(paperid);

	if(found == m_papers.end()){
		return NULL;
	}
	else{
		return &(*found).second;
	}
}

void PaperList::Delete(const int paperid)
{
	paperlist::iterator found = m_papers.find(paperid);

	if(found != m_papers.end()){
		m_papers.erase(found); 
	}
}

unsigned PaperList::Add(eblobs *blobs)
{
	std::cout << "entrée dans PaperList" << std::endl;
	static unsigned numpaper = 0;
	numpaper++;

	Paper tmp;
	tmp.id = numpaper;

	tmp.r = static_cast<double>(rand())/(static_cast<double>(RAND_MAX)+0.1);
	tmp.g = static_cast<double>(rand())/(static_cast<double>(RAND_MAX)+0.1);
	tmp.b = static_cast<double>(rand())/(static_cast<double>(RAND_MAX)+0.1);

	int num=0;
	for(eblobs::iterator iteb=blobs->begin();iteb!=blobs->end();++iteb){
		std::cout << "test" << std::endl;
		(*iteb)->SetID(tmp.id, num);
		std::cout << "test1" << std::endl;
		pt p;
		std::cout << "testi" << std::endl;
		p.id = (*iteb)->id;
		//std::cout << "test :" << (*iteb)->descs << std::endl;
		p.descs = (*iteb)->descs;
		std::cout << "testixy" << std::endl;
		p.rawx = (*iteb)->rawx;
		std::cout << "test2" << std::endl;
		p.rawy = (*iteb)->rawy;
		p.x = (*iteb)->x;
		p.y = (*iteb)->y;
		std::cout << "test3" << std::endl;
		tmp.pts.push_back(p);

		++num;
	}

	m_papers.insert(std::pair<unsigned, Paper>(numpaper, tmp));
	std::cout << "sortie dans PaperList" << std::endl;

	return numpaper;	
}

void PaperList::Clear()
{
	m_papers.clear();
}



