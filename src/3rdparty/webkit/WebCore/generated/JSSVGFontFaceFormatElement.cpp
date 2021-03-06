/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"

#if ENABLE(SVG) && ENABLE(SVG_FONTS)

#include "JSSVGFontFaceFormatElement.h"

#include "SVGFontFaceFormatElement.h"
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGFontFaceFormatElement);

/* Hash table */

static const HashTableValue JSSVGFontFaceFormatElementTableValues[2] =
{
    { "constructor", DontEnum|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGFontFaceFormatElementConstructor), (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGFontFaceFormatElementTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGFontFaceFormatElementTableValues, 0 };
#else
    { 2, 1, JSSVGFontFaceFormatElementTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSSVGFontFaceFormatElementConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGFontFaceFormatElementConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGFontFaceFormatElementConstructorTableValues, 0 };
#else
    { 1, 0, JSSVGFontFaceFormatElementConstructorTableValues, 0 };
#endif

class JSSVGFontFaceFormatElementConstructor : public DOMConstructorObject {
public:
    JSSVGFontFaceFormatElementConstructor(ExecState* exec, JSDOMGlobalObject* globalObject)
        : DOMConstructorObject(JSSVGFontFaceFormatElementConstructor::createStructure(globalObject->objectPrototype()), globalObject)
    {
        putDirect(exec->propertyNames().prototype, JSSVGFontFaceFormatElementPrototype::self(exec, globalObject), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual bool getOwnPropertyDescriptor(ExecState*, const Identifier&, PropertyDescriptor&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValue proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, StructureFlags), AnonymousSlotCount); 
    }
    
protected:
    static const unsigned StructureFlags = OverridesGetOwnPropertySlot | ImplementsHasInstance | DOMConstructorObject::StructureFlags;
};

const ClassInfo JSSVGFontFaceFormatElementConstructor::s_info = { "SVGFontFaceFormatElementConstructor", 0, &JSSVGFontFaceFormatElementConstructorTable, 0 };

bool JSSVGFontFaceFormatElementConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGFontFaceFormatElementConstructor, DOMObject>(exec, &JSSVGFontFaceFormatElementConstructorTable, this, propertyName, slot);
}

bool JSSVGFontFaceFormatElementConstructor::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSSVGFontFaceFormatElementConstructor, DOMObject>(exec, &JSSVGFontFaceFormatElementConstructorTable, this, propertyName, descriptor);
}

/* Hash table for prototype */

static const HashTableValue JSSVGFontFaceFormatElementPrototypeTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGFontFaceFormatElementPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGFontFaceFormatElementPrototypeTableValues, 0 };
#else
    { 1, 0, JSSVGFontFaceFormatElementPrototypeTableValues, 0 };
#endif

const ClassInfo JSSVGFontFaceFormatElementPrototype::s_info = { "SVGFontFaceFormatElementPrototype", 0, &JSSVGFontFaceFormatElementPrototypeTable, 0 };

JSObject* JSSVGFontFaceFormatElementPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSSVGFontFaceFormatElement>(exec, globalObject);
}

const ClassInfo JSSVGFontFaceFormatElement::s_info = { "SVGFontFaceFormatElement", &JSSVGElement::s_info, &JSSVGFontFaceFormatElementTable, 0 };

JSSVGFontFaceFormatElement::JSSVGFontFaceFormatElement(NonNullPassRefPtr<Structure> structure, JSDOMGlobalObject* globalObject, PassRefPtr<SVGFontFaceFormatElement> impl)
    : JSSVGElement(structure, globalObject, impl)
{
}

JSObject* JSSVGFontFaceFormatElement::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSSVGFontFaceFormatElementPrototype(JSSVGFontFaceFormatElementPrototype::createStructure(JSSVGElementPrototype::self(exec, globalObject)));
}

bool JSSVGFontFaceFormatElement::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGFontFaceFormatElement, Base>(exec, &JSSVGFontFaceFormatElementTable, this, propertyName, slot);
}

bool JSSVGFontFaceFormatElement::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSSVGFontFaceFormatElement, Base>(exec, &JSSVGFontFaceFormatElementTable, this, propertyName, descriptor);
}

JSValue jsSVGFontFaceFormatElementConstructor(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGFontFaceFormatElement* domObject = static_cast<JSSVGFontFaceFormatElement*>(asObject(slotBase));
    return JSSVGFontFaceFormatElement::getConstructor(exec, domObject->globalObject());
}
JSValue JSSVGFontFaceFormatElement::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSSVGFontFaceFormatElementConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}


}

#endif // ENABLE(SVG) && ENABLE(SVG_FONTS)
