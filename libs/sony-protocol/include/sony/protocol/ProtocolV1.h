#pragma once

#include "IProtocol.h"
#include "SonyProtocolSession.h"

namespace sony::protocol {

// Legacy command set spoken by WH-1000XM3/XM4 and their contemporaries.
//
// Critical: opcode 0x22 is POWER OFF on this generation (it is BATTERY GET on
// V2). Nothing in this class may ever emit it; the battery lives behind
// 0x10/0x11 instead. Speak-to-Chat is Smart Talking Mode (F6/F8 05) with a
// non-inverted enable byte — not the V2 0x0c subtype. Enable also writes
// config FC 05 (Auto / Standard ~30s); enable-only latches "do not close".
class ProtocolV1 : public IProtocol {
public:
    explicit ProtocolV1(SonyProtocolSession& session);
    ~ProtocolV1() override = default;

    [[nodiscard]] ProtocolGeneration generation() const noexcept override {
        return ProtocolGeneration::V1;
    }

    void initDevice() override;

    BatteryState getBattery() override;

    NoiseControlState getNoiseControl() override;
    void setNoiseControl(const NoiseControlState& state) override;

    EqualizerState getEqualizer() override;
    void setEqualizerPreset(int preset) override;
    void setEqualizerCustom(int clearBass, const std::array<int, 5>& bands) override;

    bool getDsee() override;
    void setDsee(bool enabled) override;

    std::string getFirmwareVersion() override;
    std::string getCodec() override;

    int getAutoPowerOff() override;
    void setAutoPowerOff(int index) override;

    bool getSpeakToChat() override;
    void setSpeakToChat(bool enabled) override;

    bool getAdaptiveVolume() override;
    void setAdaptiveVolume(bool enabled) override;

    // V1-specific surround & positioning commands
    void setVpt(int preset);
    void setSoundPosition(int preset);

private:
    SonyProtocolSession& _session;
};

} // namespace sony::protocol
