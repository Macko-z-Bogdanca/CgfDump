#pragma once

template <typename TVector, typename TComponent, int nComponents>
class TGeomSorter
{
	const TVector* m_pVertices;
	int m_nVerts;
protected:
	int m_arrSortOrder[nComponents];
public:


	TGeomSorter(const TVector* pVerts, int nVerts) :
		m_nVerts(nVerts),
		m_pVertices(pVerts)
	{
	}

	void FixSortOrder()
	{
		for (int i = 0; i < nComponents; ++i)
		{
			if (m_arrSortOrder[i] < 0) m_arrSortOrder[i] = 0;
			if (m_arrSortOrder[i] >= nComponents) m_arrSortOrder[i] = nComponents - 1;
		}
	}

	bool operator () (int nLeft, int nRight) const
	{
		if (nLeft < 0 || nLeft >= m_nVerts || nRight < 0 || nRight >= m_nVerts)
			return true;
		for (int i = 0; i < nComponents; ++i)
		{
			int nCoord = m_arrSortOrder[i];
			if (unpackComponent(m_pVertices[nLeft], nCoord) < unpackComponent(m_pVertices[nRight], nCoord))
				return true;
			else
				if (unpackComponent(m_pVertices[nLeft], nCoord) > unpackComponent(m_pVertices[nRight], nCoord))
					return false;
		}
		return true;
	}
};