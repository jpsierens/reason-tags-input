import React from 'react';
import { shallow, mount, configure } from 'enzyme';
import Adapter from 'enzyme-adapter-react-15';

import TagsInput from '../build';

configure({ adapter: new Adapter() });


describe('<TagsInput />', () => {
	it('should render', () => {
		expect(shallow(<TagsInput />).find('.reason-tags-input').length).toBe(1);
	});

	it('should create a tag when the user enters text', () => {
		const onInput = () => false;
		const onRemove = () => false;
		const tagsInput = mount(<TagsInput onInput={onInput} onRemove={onRemove} />);
		tagsInput.setState(
			{
				reasonState: [
					["testTag", ""],
					...tagsInput.state().reasonState.slice(1)
				],
				reasonStateVersion: 1,
				reasonStateVersionUsedToComputeSubelements: 1
			}
		);
		console.log(tagsInput.state())
		console.log(tagsInput.find('.tag').length);
	});

	it('should render clear cta', () => {
		const tagsInput = shallow(<TagsInput onClear={() => 0} />);
		expect(tagsInput.find('.clear-all').length).toBe(1);
	});

	it('should render clear cta\'s default text', () => {
		const tagsInput = shallow(<TagsInput onClear={() => 0} />);
		expect(tagsInput.find('.clear-all').text()).toBe('Clear all');
	});

	it('should render clear cta\'s custom text', () => {
		const tagsInput = shallow(<TagsInput clearAllText="custom" onClear={() => 0} />);
		expect(tagsInput.find('.clear-all').text()).toBe('custom');
	});
});
