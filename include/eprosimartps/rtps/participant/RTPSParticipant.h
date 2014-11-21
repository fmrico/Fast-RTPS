/*************************************************************************
 * Copyright (c) 2014 eProsima. All rights reserved.
 *
 * This copy of eProsima RTPS is licensed to you under the terms described in the
 * EPROSIMARTPS_LIBRARY_LICENSE file included in this distribution.
 *
 *************************************************************************/

/**
 * @file RTPSParticipant.h
*/


#ifndef RTPSParticipant_H_
#define RTPSParticipant_H_

//#include <stdio.h>
//#include <stdlib.h>
//#include <sys/types.h>
//
//#if defined(_WIN32)
//#include <process.h>
//#else
//#include <unistd.h>
//#endif

#include <cstdlib>
#include "eprosimartps/config/eprosimartps_dll.h"
#include "eprosimartps/rtps/common/Guid.h"

namespace eprosima {
namespace rtps {

class RTPSParticipantImpl;

/**
 * @brief Class RTPSParticipant, contains the public API for a RTPSParticipant.
 * @ingroup MANAGEMENTMODULE
 */
class RTPS_DllAPI RTPSParticipant
{
	friend class RTPSParticipantImpl;
public:
	RTPSParticipant(RTPSParticipantImpl* pimpl);
	virtual ~ RTPSParticipant();
	//!Get the GUID_t of the RTPSParticipant.
	const GUID_t& getGuid() const ;
	//!Force the announcement of the RTPSParticipant state.
	void announceRTPSParticipantState();
	//!Method to loose the next change (ONLY FOR TEST).
	void loose_next_change();
	//!Stop the RTPSParticipant announcement period.
	void stopRTPSParticipantAnnouncement();
	//!Reset the RTPSParticipant announcement period.
	void resetRTPSParticipantAnnouncement();

	bool newRemoteWriterDiscovered(const GUID_t& pguid, int16_t userDefinedId);
	bool newRemoteReaderDiscovered(const GUID_t& pguid, int16_t userDefinedId);

	uint32_t getRTPSParticipantID() const;
	private:
	RTPSParticipantImpl* mp_impl;
};


} /* namespace rtps */
} /* namespace eprosima */

#endif /* RTPSParticipant_H_ */




