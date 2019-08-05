// Copyright 2019 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file DomainParticipantImpl.h
 *
 */

#ifndef _FASTDDS_PARTICIPANTIMPL_HPP_
#define _FASTDDS_PARTICIPANTIMPL_HPP_
#ifndef DOXYGEN_SHOULD_SKIP_THIS_PUBLIC
#include <fastdds/rtps/common/Guid.h>
#include <fastdds/rtps/participant/RTPSParticipantListener.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastdds/rtps/reader/StatefulReader.h>

#include <fastdds/dds/publisher/qos/PublisherQos.hpp>
#include <fastdds/dds/subscriber/qos/SubscriberQos.hpp>

#include <fastdds/dds/topic/TypeSupport.hpp>

namespace eprosima{
namespace fastrtps{

namespace rtps{
class RTPSParticipant;
class WriterProxyData;
class ReaderProxyData;
}

class PublisherAttributes;
class SubscriberAttributes;

} // namespace fastrtps

namespace fastdds {
namespace dds {

class DomainParticipant;
class DomainParticipantListener;
class Publisher;
class PublisherImpl;
class PublisherListener;
class Subscriber;
class SubscriberImpl;
class SubscriberListener;


/**
 * This is the implementation class of the DomainParticipant.
 * @ingroup FASTRTPS_MODULE
 */
class DomainParticipantImpl
{
    friend class DomainParticipantFactory;

private:

    DomainParticipantImpl(
            const fastrtps::ParticipantAttributes& patt,
            DomainParticipant* pspart,
            DomainParticipantListener* listen = nullptr);

    virtual ~DomainParticipantImpl();

public:

    bool set_listener(
            DomainParticipantListener* listener)
    {
        listener_ = listener;
        return true;
    }

    const DomainParticipantListener* get_listener() const
    {
        return listener_;
    }

    /**
     * Create a Publisher in this Participant.
     * @param qos QoS of the Publisher.
     * @param att Attributes of the Publisher.
     * @param listen Pointer to the listener.
     * @return Pointer to the created Publisher.
     */
    Publisher* create_publisher(
            const fastdds::dds::PublisherQos& qos,
            const fastrtps::PublisherAttributes& att,
            PublisherListener* listen = nullptr);

    bool delete_publisher(
            Publisher* publisher);

    /**
     * Create a Subscriber in this Participant.
     * @param qos QoS of the Subscriber.
     * @param att Attributes of the Subscriber
     * @param listen Pointer to the listener.
     * @return Pointer to the created Subscriber.
     */
    Subscriber* create_subscriber(
            const fastdds::dds::SubscriberQos& qos,
            const fastrtps::SubscriberAttributes& att,
            SubscriberListener* listen = nullptr);

    bool delete_subscriber(
            Subscriber* subscriber);

    /**
     * Register a type in this participant.
     * @param type The TypeSupport to register. A copy will be kept by the participant until removed.
     * @param type_name The name that will be used to identify the Type.
     * @return True if registered.
     */
    bool register_type(
            TypeSupport type,
            const std::string& type_name);

    /**
     * Unregister a type in this participant.
     * @param typeName Name of the type
     * @return True if unregistered.
     */
    bool unregister_type(
            const char* typeName);

    // TODO create/delete topic

    // TODO Subscriber* get_builtin_subscriber();

    /* TODO
    bool ignore_participant(
            const fastrtps::rtps::InstanceHandle_t& handle);
    */

    /* TODO
    bool ignore_topic(
            const fastrtps::rtps::InstanceHandle_t& handle);
    */

    /* TODO
    bool ignore_publication(
            const fastrtps::rtps::InstanceHandle_t& handle);
    */

    /* TODO
    bool ignore_subscription(
            const fastrtps::rtps::InstanceHandle_t& handle);
    */

    uint8_t get_domain_id() const;

    // TODO bool delete_contained_entities();

    bool assert_liveliness();

    bool set_default_publisher_qos(
            const fastdds::dds::PublisherQos& qos);

    const fastdds::dds::PublisherQos& get_default_publisher_qos() const;

    bool set_default_subscriber_qos(
            const fastdds::dds::SubscriberQos& qos);

    const fastdds::dds::SubscriberQos& get_default_subscriber_qos() const;

    // TODO Get/Set default Topic Qos

    /* TODO
    bool get_discovered_participants(
            std::vector<fastrtps::rtps::InstanceHandle_t>& participant_handles) const;
    */

    /* TODO
    bool get_discovered_participant_data(
            ParticipantBuiltinTopicData& participant_data,
            const fastrtps::rtps::InstanceHandle_t& participant_handle) const;
    */

    /* TODO
    bool get_discovered_topics(
            std::vector<fastrtps::rtps::InstanceHandle_t>& topic_handles) const;
    */

    /* TODO
    bool get_discovered_topic_data(
            TopicBuiltinTopicData& topic_data,
            const fastrtps::rtps::InstanceHandle_t& topic_handle) const;
    */

    bool contains_entity(
            const fastrtps::rtps::InstanceHandle_t& handle,
            bool recursive = true) const;

    bool get_current_time(
            fastrtps::Time_t& current_time) const;

    const DomainParticipant* get_participant() const;

    DomainParticipant* get_participant();

    const fastrtps::rtps::RTPSParticipant* rtps_participant() const
    {
        return rtps_participant_;
    }

    fastrtps::rtps::RTPSParticipant* rtps_participant()
    {
        return rtps_participant_;
    }

    const TypeSupport find_type(
            const std::string& type_name) const;

    const fastrtps::rtps::InstanceHandle_t& get_instance_handle() const;

    // From here legacy RTPS methods.

    const fastrtps::rtps::GUID_t& guid() const;

    /**
     * Get the participant attributes
     * @return Participant attributes
     */
    inline const fastrtps::ParticipantAttributes& get_attributes() const
    {
        return att_;
    }

    std::vector<std::string> get_participant_names() const;

    /**
     * This method can be used when using a StaticEndpointDiscovery mechanism differnet that the one
     * included in FastRTPS, for example when communicating with other implementations.
     * It indicates the Participant that an Endpoint from the XML has been discovered and
     * should be activated.
     * @param partguid Participant GUID_t.
     * @param userId User defined ID as shown in the XML file.
     * @param kind EndpointKind (WRITER or READER)
     * @return True if correctly found and activated.
     */
    bool new_remote_endpoint_discovered(
            const fastrtps::rtps::GUID_t& partguid,
            uint16_t userId,
            fastrtps::rtps::EndpointKind_t kind);

    fastrtps::rtps::ResourceEvent& get_resource_event() const;

    //! Remove all listeners in the hierarchy to allow a quiet destruction
    void disable();

private:

    //!Participant Attributes
    fastrtps::ParticipantAttributes att_;

    //!RTPSParticipant
    fastrtps::rtps::RTPSParticipant* rtps_participant_;

    //!Participant*
    DomainParticipant* participant_;

    //!Participant Listener
    DomainParticipantListener* listener_;

    //!Publisher maps
    std::map<Publisher*, PublisherImpl*> publishers_;
    std::map<fastrtps::rtps::InstanceHandle_t, Publisher*> publishers_by_handle_;
    mutable std::mutex mtx_pubs_;

    PublisherQos default_pub_qos_;

    //!Subscriber maps
    std::map<Subscriber*, SubscriberImpl*> subscribers_;
    std::map<fastrtps::rtps::InstanceHandle_t, Subscriber*> subscribers_by_handle_;
    mutable std::mutex mtx_subs_;

    SubscriberQos default_sub_qos_;

    //!TopicDataType map
    std::map<std::string, TypeSupport> types_;
    mutable std::mutex mtx_types_;

    class MyRTPSParticipantListener : public fastrtps::rtps::RTPSParticipantListener
    {
        public:

            MyRTPSParticipantListener(DomainParticipantImpl* impl)
                : participant_(impl)
            {}

            virtual ~MyRTPSParticipantListener() override
            {}

            void onParticipantDiscovery(
                    fastrtps::rtps::RTPSParticipant* participant,
                    fastrtps::rtps::ParticipantDiscoveryInfo&& info) override;

#if HAVE_SECURITY
            void onParticipantAuthentication(
                    fastrtps::rtps::RTPSParticipant* participant,
                    fastrtps::rtps::ParticipantAuthenticationInfo&& info) override;
#endif

            void onReaderDiscovery(
                    fastrtps::rtps::RTPSParticipant* participant,
                    fastrtps::rtps::ReaderDiscoveryInfo&& info) override;

            void onWriterDiscovery(
                    fastrtps::rtps::RTPSParticipant* participant,
                    fastrtps::rtps::WriterDiscoveryInfo&& info) override;

            DomainParticipantImpl* participant_;

    } rtps_listener_;

    bool exists_entity_id(
            const fastrtps::rtps::EntityId_t& entity_id) const;

};

} /* namespace dds */
} /* namespace fastdds */
} /* namespace eprosima */
#endif
#endif /* _FASTDDS_PARTICIPANTIMPL_HPP_ */
