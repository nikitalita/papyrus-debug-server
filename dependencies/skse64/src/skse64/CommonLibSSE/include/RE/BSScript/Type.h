#pragma once


namespace RE
{
	namespace BSScript
	{
		class Class;


		class Type
		{
		public:
			Type();
			explicit Type(VMTypeID a_type);
			explicit Type(const Type& a_rhs);

			VMTypeID	GetTypeID() const;
			void		SetTypeID(VMTypeID a_type);
			VMTypeID	GetUnmangledType() const;
			Class*		GetScriptClass() const;
			bool		IsObject(void)	const;
			bool 		IsInt() const;
			bool 		IsFloat() const;
			bool 		IsString() const;
			bool 		IsBool() const;
			bool 		IsObjectArray() const;
			bool 		IsLiteralArray() const;
			bool 		IsArray() const;

		protected:
			// members
			VMTypeID type;	// 00
		};
		STATIC_ASSERT(sizeof(Type) == 0x8);
	}
}
