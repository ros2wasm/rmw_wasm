#ifndef WASM_CPP__PARTICIPANT_HPP_
#define WASM_CPP__PARTICIPANT_HPP_

#include <string>
#include <optional>


namespace wasm_cpp
{
    class Participant
    {

    public:

        explicit Participant(
            const std::string & name,
            const std::string & role
        );

        virtual ~Participant();

        const std::string & get_name() const;

        const std::string & get_role() const;

        const std::string & get_gid() const;

    private:

        const std::string m_name;
        const std::string m_role;
        std::string m_gid;

        void is_valid_name() const;
        void is_valid_role() const;
        void registration();
        void deregistration();

    };

} // namespace wasm_cpp

#endif // WASM_CPP__PARTICIPANT_HPP_
