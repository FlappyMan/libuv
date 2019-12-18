#include "OrderThread.h"
#include "DBThread.h"
#include "BackTrade_Marco.h"
#include "MatchThread.h"

using namespace std;

int main()
{
	COrderThread ot;
	CDBThread dt;
	CMatchThread mt;

	dt.getOrderThread(ot);
	dt.getMatchThread(mt);
	mt.getDBThread(dt);

	ot.Start();
	dt.Start();
	mt.Start();

	mt.Join();
	dt.Join();
	ot.Join();

	return 0;
}
