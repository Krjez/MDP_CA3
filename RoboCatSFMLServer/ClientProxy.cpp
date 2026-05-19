/*
*  Provided in class, unedited
*/

#include "RoboCatServerPCH.hpp"


ClientProxy::ClientProxy(const SocketAddress& inSocketAddress, const string& inName, int inPlayerId) : 
	mSocketAddress(inSocketAddress),
	mName(inName),
	mPlayerId(inPlayerId),
	mDeliveryNotificationManager(false, true),
	mIsLastMoveTimestampDirty(false)
{
	UpdateLastPacketTime();
}


void ClientProxy::UpdateLastPacketTime()
{
	mLastPacketFromClientTime = Timing::sInstance.GetTimef();
}

