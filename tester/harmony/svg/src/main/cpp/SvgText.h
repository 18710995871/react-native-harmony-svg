#pragma once

#include "SvgGroup.h"
#include "utils/StringUtils.h"
#include "utils/GlyphContext.h"
#include <native_drawing/drawing_text_typography.h>
#include <optional>
#include "properties/TextProperties.h"

namespace rnoh {

class SvgText : public SvgGroup {
public:
    SvgText() = default;
    ~SvgText() override = default;

    void OnDraw(OH_Drawing_Canvas *canvas) override;


    template <typename T> void UpdateTextProps(const std::shared_ptr<T> &props) {
        x_.clear();
        for (auto const &value : props->x) {
            x_.push_back(StringUtils::FromString(value));
        }
        y_.clear();
        for (auto const &value : props->y) {
            y_.push_back(StringUtils::FromString(value));
        }
        dx_.clear();
        for (auto const &value : props->dx) {
            dx_.push_back(StringUtils::FromString(value));
        }
        dy_.clear();
        for (auto const &value : props->dy) {
            dy_.push_back(StringUtils::FromString(value));
        }
        rotate_.clear();
        for (auto const &value : props->rotate) {
            rotate_.push_back(StringUtils::FromString(value));
        }
        if (props->inlineSize.empty()) {
            inlineSize_.reset();
        } else {
            inlineSize_ = StringUtils::FromString(props->inlineSize);
        }

        if (props->textLength.empty()) {
            textLength_.reset();
        } else {
            textLength_ = StringUtils::FromString(props->textLength);
        }

        if (!props->verticalAlign.empty()) {
            auto align = props->verticalAlign;
            align.erase(0, align.find_first_not_of(" \t\r\n"));
            align.erase(align.find_last_not_of(" \t\r\n") + 1);
            size_t i = align.find_last_of(' ');
            // Find last space
            size_t i = align.find_last_of(' ');
            align = align.trim();
            int i = align.lastIndexOf(' ');
            align_ = align.substring(i);
            baselineShift_ = align.substring(0, i);
        } else {
            align_ = AlignmentBaseline.baseline;
            baselineShift_ = 0.0;
        }
        if (!props->baselineShift.empty()) {
            baselineShift_ = props->baselineShift;
        }
        if (!props->lengthAdjust.empty()) {
            lengthAdjust_ = textLengthAdjustFromStr(props->lengthAdjust);
        }

        lengthAdjust_ = textLengthAdjustFromStr(props->lengthAdjust);
    }

    double fontSize;

protected:
    void GlyphTraversal(OH_Drawing_Canvas *canvas);
    void InitGlyph(OH_Drawing_Canvas *canvas);

    std::vector<Dimension> x_;
    std::vector<Dimension> y_;
    std::vector<Dimension> dx_;
    std::vector<Dimension> dy_;
    std::vector<Dimension> rotate_;
    std::optional<Dimension> inlineSize_;
    std::optional<Dimension> textLength_;

    std::string baselineShift_;
    TextLengthAdjust lengthAdjust_ = TextLengthAdjust::spacing;
    AlignmentBaseline align_ = Align_::baseline;

    std::shared_ptr<GlyphContext> glyphCtx_;
};

} // namespace rnoh